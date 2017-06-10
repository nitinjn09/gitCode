#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <ifaddrs.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/types.h>

#define TRUE 1
#define FALSE 0
#define INVALID_FD 10000

/*
Recieved data formate: <time><num_of_group><mcast_groups>#<data_type>#<data>
Sent data formate: <mcast_group>#<data_type>/<data>

type of data:  1. registration request
               2. 
               3. 
*/

typedef struct clinet_list
{
  bool present;     // Client connected or not
  int  client_fd;    //client_socket
  int  num_of_groups;
  int  groups[10];        // multicast group
}client_list;


int server_socket;
int mcast_group[10];                // Supporting 10 mcast group and each can have 10 clients.
int type_of_data;                    // 0-normal hi, 1-
int client_num;   // number of client joined till now.
int pos;
int mcast_group_list[50];
client_list client_joined[10];


fd_set read_fd_set;


bool search_list(int item, int list[], int length)
{
  int i;
  for (i = 0; i < length; i++) {
    if (list[i] == item) {
      return TRUE;
    }
  }
  return FALSE;
}

void parse_data(int id, char recvBuff[], char timeBuff[], char data_buff[])
{
    int i = 0, k = 0, j = 0;
    char temp_buff[4];

    while(recvBuff[i]!='#') {
       timeBuff[k] = recvBuff[i];
       i++;
       k++;
    }
    timeBuff[k] = '\n';
    timeBuff[k] = '\0';
    i++;
    k = 0;
    while(recvBuff[i] != '#') {
      client_joined[id].num_of_groups = atoi(&recvBuff[i]);
      i++;
    }
    i++;
    while(recvBuff[i]!='#') {
      bzero(temp_buff, sizeof(temp_buff));
      while(recvBuff[i] != '$') {
        temp_buff[k] = recvBuff[i];
        i++;
        k++;
      }
      client_joined[id].groups[j] = atoi(temp_buff);
      if(!search_list(client_joined[id].groups[j], mcast_group_list, pos+1)) {
         mcast_group_list[pos++] = client_joined[id].groups[j];
      }   
      i++;
      j++;
      k = 0;
    }
    i++;
    while(recvBuff[i]!='#') {
       type_of_data = atoi(&recvBuff[i]);
       i++;
    }
    i++;
    while(recvBuff[i] != '\0') {
      data_buff[k] = recvBuff[i];
      i++;
      k++;
    }
    data_buff[k] = '\0';
}


void *recv_data()
{
  char recvBuff[1024], data_buff[1024], timeBuff[40];
  //int msg_count = 0;
  int client_id;
  int i;

  //signal(SIGBUS,SIG_IGN);
  while(1) {
    client_id = 0;
    if (client_num > 0) {
        for (; ((client_id < client_num) && client_joined[client_id].present); client_id++) {
          bzero(recvBuff, sizeof(recvBuff));
          memset(timeBuff, '0', sizeof(timeBuff));
          memset(data_buff, '0', sizeof(data_buff));
          if (recv(client_joined[client_id].client_fd,recvBuff,sizeof(recvBuff), 0) <= 0) {
              close(client_joined[client_id].client_fd);
              client_joined[client_id].present = 0;
              //client_joined[client_id].client_fd = INVALID_FD;
              perror("ERROR reading from socket");
              printf("\nConnection lost with client-%d\n",client_id);
          }
          parse_data(client_id, recvBuff, timeBuff, data_buff);

          printf("Client-%d: num_of_groups: %d", client_joined[client_id].client_fd, client_joined[client_id].num_of_groups);
          printf(" mcast_groups: ");
          for(i = 0; i< client_joined[client_id].num_of_groups; i++) {
            printf("%d ",client_joined[client_id].groups[i]);
          }
          printf(" type_of_data: %d, Data: %s\n", type_of_data, data_buff);
           
          //printf("message recieved count from client %d is %d\n",client_id,msg_count++);
        }
    } else {
    printf("No data to read from clients\n");
    sleep(5);
    }
  }
}

void *send_data()
{
  signal(SIGPIPE,SIG_IGN);
  char sendBuff[1024];
  time_t ticks; 
  int client_id;
  
  while(1) {
    client_id = 0;
    if (client_num > 0) {
        
        for (; ((client_id < client_num) && client_joined[client_id].present); client_id++) {
         /* Write a response to the client */
         bzero(sendBuff,sizeof(sendBuff));
         ticks = time(NULL);
         snprintf(sendBuff,sizeof(sendBuff), "%.24s\r#%d#%d#Server says Hi..",ctime(&ticks), 1, 2);
         if (send(client_joined[client_id].client_fd,sendBuff, sizeof(sendBuff), 0) < 0) {
             client_joined[client_id].present = 0;
             perror("ERROR writing to socket");
             printf("\nConnection lost with client-%d\n",client_id);
         }
         sleep(1);
        }
    } else {
       printf("No client connected yet\n");
       sleep(3);
    }
  }
}


void *accept_clients_connection()
{
  pthread_t tid_rd;
  pthread_attr_t attr_rd;
  struct sockaddr_in client_addr;
  socklen_t addr_size = sizeof(struct sockaddr_in); 
  char clientip[12];
  int clientport, flag = 0;

  FD_ZERO(&read_fd_set);

  while (1) {
    while(client_num < 10) {
       client_joined[client_num].client_fd = accept(server_socket, (struct sockaddr*)NULL, NULL);
       FD_SET (client_joined[client_num].client_fd, &read_fd_set);
       client_joined[client_num].present = 1;
       memset(&client_addr, '0', sizeof(client_addr));
       memset(&clientip, '0', sizeof(clientip));
       getpeername(client_joined[client_num].client_fd, (struct sockaddr *)&client_addr, &addr_size); 
       strcpy(clientip, inet_ntoa(client_addr.sin_addr));
       printf("\nClient %s :%d connected with socket: %d.\n\n",clientip,(int)ntohs(client_addr.sin_port),client_joined[client_num].client_fd);
       client_num++;
       if (flag == 0) {
           pthread_attr_init(&attr_rd);
           if (pthread_create(&tid_rd, &attr_rd, recv_data, NULL)) {
               perror("ERROR: Pthread create error recv_data. Exiting...");
               exit(EXIT_FAILURE);
           }
           flag = 1;
       }
     }
    printf("all sockets occupied\n");
  }
}

int main(int argc, char *argv[]) 
{
  struct sockaddr_in serv_addr;
  int choice;
  pthread_t tid_sd, tid_acc;
  struct ifaddrs *if_addr, *tmp;
  
  pthread_attr_t attr_sd, attr_acc;
  

  memset(&serv_addr, '0', sizeof(serv_addr));
 
  /* Get the interface address of the local machine and assign that to server address */
  if (getifaddrs(&if_addr) == -1) {
      perror("getifaddrs");
      exit(EXIT_FAILURE);
  }

  tmp = if_addr;
  while (tmp) {
    if (tmp->ifa_addr && (tmp->ifa_addr->sa_family == AF_INET)) {
        struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
        if (strcmp(inet_ntoa(pAddr->sin_addr), "127.0.0.1") != 0) {
            printf("\nServer adress: %s\n\n", inet_ntoa(pAddr->sin_addr));
            serv_addr.sin_addr.s_addr = inet_addr(inet_ntoa(pAddr->sin_addr));
            break;
        }
    }
    tmp = tmp->ifa_next;
  }

  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(5000); 
  /* Create server socket */
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  /* Bind server socket to address */
  bind(server_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
  /* Create queue to listen on the socket */
  listen(server_socket, 1000);

  pthread_attr_init(&attr_acc);
  if (pthread_create(&tid_acc, &attr_acc, accept_clients_connection, NULL)) {
      printf("\nERROR: Pthread create error accept_clients_connection. Exiting...");
      exit(EXIT_FAILURE);
  }

 /* Create thread to send data to clients */
  pthread_attr_init(&attr_sd);
  if (pthread_create(&tid_sd, &attr_sd, send_data, NULL)) {
      printf("\nERROR: Pthread create error send_data. Exiting...");
      exit(EXIT_FAILURE);
  }

  while(1) {

    printf("\nmcast_group_list: ");
    for (int i = 0; i < pos; i++)
    {
      printf("%d ",mcast_group_list[i]);
    }
    printf("\n");
   /*
    printf("\nEnter your choice:: \n 0. Exit \n 1. Send data to client \n 2. Recieve data from client \n ");
    scanf("%d", &choice);

    switch(choice) {

      case 1: send_data();
      break;

      case 2: recv_data();
      break;

      case 0: exit(1);

      default: printf("\n Invalid choice. Enter again\n");
      break;
    }
   */ 
    sleep(5);
  }
  return 0;
}

