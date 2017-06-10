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


/*
Recieved data formate: <mcast_group>#<data_type>#<Data>

Sent data formate: <mcast_group>#<data_type>/<data>
*/

typedef struct clinet_list
{
  bool present;     // Client connected or not
  int  client_id;    //client_socket
  int  group;        // multicast group
}client_list;

struct sockaddr_in serv_addr;
int server_socket, client_socket[10];   // supporting 10 clients.
int mcast_group[10];                // Supporting 10 mcast group and each can have 10 clients.
int type_of_data;                       // 0-normal hi, 1-
client_list clients[100];
int client_num;
int mcast_group_list[255];



void analyze_data(char recvBuff[], char timeBuff[], char buffer[])
{
  int i=0,k=0;
    while(recvBuff[i]!='#') {
       timeBuff[k] = recvBuff[i];
       i++;
       k++;
    }
    timeBuff[k++] = '\n';
    timeBuff[k] = '\0';
    i++;
    k = 0;
    while(recvBuff[i]!='#') {
       //while(recvBuff[i] != '$') {
         mcast_group[0] = atoi(&recvBuff[i]);
        // k++;
      // }
       i++;
    }
    i++;
    while(recvBuff[i]!='#') {
       type_of_data = atoi(&recvBuff[i]);
       i++;
    }
    i++;
    while(recvBuff[i] != '\0') {
      buffer[k] = recvBuff[i];
      i++;
      k++;
    }
    buffer[k] = '\0';
}


void *recv_data()
{
  char recvBuff[1024], buffer[1024], timeBuff[40];
  int client_id = client_num;
  int msg_count = 0;

  printf("\nYou are in recv_data function. thread running for client %d\n\n",client_id);

  while(1) {
      bzero(recvBuff, sizeof(recvBuff));
      memset(timeBuff, '0', sizeof(timeBuff));
      memset(buffer, '0', sizeof(buffer));
      if (read(client_socket[client_id],recvBuff,sizeof(recvBuff)) < 0) {
          perror("ERROR reading from socket");
          exit(EXIT_FAILURE);
      }
      analyze_data(recvBuff, timeBuff, buffer);
      //printf("Client-%d: %s: mcast_groups: %d, type_of_data: %d, Data: %s\n",client_id, timeBuff, mcast_group[0], type_of_data, buffer);
      //printf("Client-%d",client_id);
      //for (i = 0; i < )
      printf("message recieved count from client %d is %d\n",client_id,msg_count++);
      sleep(1);
  }
}

void *send_data()
{
  struct sockaddr_in client_addr;
  char sendBuff[1024], clientip[12];
  int clientport;
  time_t ticks;
  socklen_t addr_size = sizeof(struct sockaddr_in);  
  int client_id = 1;
  
  printf("\nYou are in send_data function\n");

  memset(&client_addr, '0', sizeof(client_addr));
  memset(&clientip, '0', sizeof(clientip));

  /* Establish  connection with client*/
 // client_socket[0] = accept(server_socket, (struct sockaddr*)NULL, NULL);
  while(1) {
    client_id = 1;
    if (client_num > 0) {
        /*   getpeername(client_socket[client_num], (struct sockaddr *)&client_addr, &addr_size); 
        strcpy(clientip, inet_ntoa(client_addr.sin_addr));
        printf("Client connected. Address:   %s:%d :: %d\n",clientip,(int)ntohs(client_addr.sin_port),client_socket[client_num]);
        */
        for (; client_id <= client_num; client_id++) {
         /* Write a response to the client */
         bzero(sendBuff,sizeof(sendBuff));
         ticks = time(NULL);
         snprintf(sendBuff,sizeof(sendBuff), "%.24s\r#%d#%d#Server says Hi..",ctime(&ticks), 1, 2);
         if (write(client_socket[client_id],sendBuff, sizeof(sendBuff)) < 0) {
             perror("ERROR writing to socket");
             exit(EXIT_FAILURE);
         }
         sleep(1);
        }
    } else {
       printf("No client connected yet\n");
       sleep(1);
    }
  }
}


void *accept_clients_connection()
{
pthread_t tid_rd[10];
pthread_attr_t attr_rd[10];

while (1) {
 while(client_num < 10) {
   client_socket[++client_num] = accept(server_socket, (struct sockaddr*)NULL, NULL);
   printf("\nClient-%d connected.\n",client_num);
       pthread_attr_init(&attr_rd[client_num]);
       if (pthread_create(&tid_rd[client_num], &attr_rd[client_num], recv_data, NULL)) {
           printf("\nERROR: Pthread create error recv_data. Exiting...");
           exit(EXIT_FAILURE);
        }
        printf("thread %d created\n", client_num);
  }
 printf("all sockets occupied\n");
 }
}

int main(int argc, char *argv[]) 
{
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
            printf("\nServer adress: %s\n", inet_ntoa(pAddr->sin_addr));
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

