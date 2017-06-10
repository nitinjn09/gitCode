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

#define TRUE 1
#define FALSE 0

/*
Recieved data formate: <time><num_of_group><mcast_groups>#<data_type>#<data>
Sent data formate: <mcast_group>#<data_type>/<data>

type of data:  1. registration request
               2. 
               3. 
*/

typedef struct clinet_list
{
  int  client_fd;   //client_socket
  int  num_of_groups;
  int  groups[10];        // multicast group
  struct client_list *next;
}client_list;

typedef struct mcast_group_client   // maintain list of client in each mcast group
{
  int group;
  int num_of_clients;
  struct client_list *c_list;
  struct mcast_group_client *next;
}mcast_group_client;



//struct mcast_group_client *mgc_head = NULL;
//mcast_group_client mgc[50];

int server_socket;
int type_of_data;                    // 0-normal hi, 1-
int client_num;   // number of client joined till now.
int pos;
int mcast_group_list[50];  //list of mcast groups present
mcast_group_client mgc[50];


client_list *cl_head = NULL;



bool search_list(int item, int list[], int length)
{
  int i;
  for (i = 0; i < length; i++) {
    if (mgc[i].group == item) {
      return TRUE;
    }
  }
  return FALSE;
}

void print_client_list()
{
  client_list *temp = cl_head;
  printf("\nClient_list: ");
  while(temp != NULL) {
    printf("%d ",temp->client_fd);
    temp = temp->next;
  }
  printf("\n");
}

void print_mcast_group_list()
{
  int i;
  client_list *temp;
  printf("\n mcast_group_list: ");
  for (i = 0; i < pos; i++) {
      printf("%d : ",mgc[i].group);
      //printf("\nNitin-3\n");
      temp = mgc[i].c_list;
      while(temp != NULL) {
        //printf("\nNitin-4\n");
        printf("%d ",temp->client_fd);
        //printf("\nNitin-6\n");
        temp = temp->next;
        //printf("\nNitin-6\n");
      }
      printf("\n");
    }
    printf("\n");

}

/* Add client to existing list at the end */
void add_client(int fd) 
{
  client_list *temp = cl_head;
  client_list *node  = (client_list*)malloc(sizeof(client_list*));
  if(node == NULL) {
    printf("\nMalloc failed for client %d\n",fd);
    return;
  }
  node->client_fd = fd;
  node->next = NULL;

  if (cl_head == NULL) {
    cl_head = node;
    printf("1. Node added: %d\n", node->client_fd);
    print_client_list();
    return;
  }

  while(temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = node;
  printf("2. Node added: %d\n", node->client_fd);
  print_client_list();
  return;
}

void add_client_in_group_list(client_list *node, int position) 
{
  client_list *temp = (client_list*)malloc(sizeof(client_list*));
  client_list *temp_1 = mgc[position].c_list;
  if(temp == NULL) {
    printf("\nMalloc failed for client %d\n",temp->client_fd);
    return;
  }
  //printf("\nNitin-7\n");
  if (mgc[position].c_list == NULL) {
    mgc[position].c_list = temp;
    temp->next = NULL;
    //printf("\nNitin-7-1\n");
    return;
  }
 // printf("\nNitin-8\n");
  while(temp_1->next != NULL) {
    temp_1 = temp_1->next;
  }
  //printf("\nNitin-9\n");
  temp_1->next = temp;
  temp->next = NULL;
  //printf("\nNitin-10\n");
  return;
}

void add_client_to_mcast_group_list(client_list *temp)
{
  int i,j;
  for (i = 0; i < pos; i++) {
    for(j =0; j < temp->num_of_groups; j++) {
      if (mgc[i].group == temp->groups[j]) {
        printf("\nNitin-2\n");
        add_client_in_group_list(temp, i);
        break;
      }
    }
  }
}

/* If some client disconnect, then remove that from client_list */

void delete_client(client_list *node)
{
  int i = 0;

  close(node->client_fd);
  client_list *temp_p = cl_head, *temp_n = cl_head;;
  if(cl_head == NULL) {
    printf("ERROR: Empty list\n");
    return;
  }
  while (temp_n != node) {
    temp_p = temp_n;
    temp_n = temp_n->next;
  }
  temp_p->next = temp_n->next;
  free(node);
  return;
}

void parse_data(client_list *temp, char recvBuff[], char timeBuff[], char data_buff[])
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
      temp->num_of_groups = atoi(&recvBuff[i]);
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
      temp->groups[j] = atoi(temp_buff);
      if(!search_list(temp->groups[j], mgc, pos)) {
         mgc[pos].group = temp->groups[j];
         pos++;
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
  int i, flag = 0;
  client_list *temp = cl_head;

  //signal(SIGBUS,SIG_IGN);
  while(1) {
    if (cl_head == NULL) {
       printf("No data to read from clients\n");
       sleep(1);
    }
    else {
      temp = cl_head;
      while(temp != NULL) {
        bzero(recvBuff, sizeof(recvBuff));
        memset(timeBuff, '0', sizeof(timeBuff));
        memset(data_buff, '0', sizeof(data_buff));
        //printf("\nrecv fd = %d\n", temp->client_fd);
        if (recv(temp->client_fd,recvBuff,sizeof(recvBuff), 0) == 0) {
            printf("nNitin-1");
            delete_client(temp);
            perror("ERROR reading from socket");
          }
          parse_data(temp, recvBuff, timeBuff, data_buff);
          //add_client_to_mcast_group_list(temp);
          //printf("\nNitin-1\n");
          printf("Client-%d: num_of_groups: %d", temp->client_fd, temp->num_of_groups);
          printf(" mcast_groups: ");
          for(i = 0; i< temp->num_of_groups; i++) {
            printf("%d ",temp->groups[i]);
          }
          printf(" type_of_data: %d, Data: %s\n", type_of_data, data_buff);
          temp = temp->next;
          sleep(1);
      }
    }
  }
}

void *send_data()
{
  signal(SIGPIPE,SIG_IGN);
  char sendBuff[1024];
  time_t ticks; 
  client_list *temp;
  
  while(1) {
    if (cl_head == NULL) {
      printf("No client connected yet\n");
      sleep(1);
    }
    else {
      temp = cl_head;
      while (temp != NULL) {
        /* Write a response to the client */
        bzero(sendBuff,sizeof(sendBuff));
        ticks = time(NULL);
        snprintf(sendBuff,sizeof(sendBuff), "%.24s\r#%d#%d#Server says Hi..",ctime(&ticks), 1, 2);
        //printf("\nsend fd = %d\num_of_group", temp->client_fd);
        if (send(temp->client_fd,sendBuff, sizeof(sendBuff), 0) < 0) {
            //delete_client(temp);
            perror("ERROR writing to socket");
        }
        temp = temp->next;
        sleep(1);
      }
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
  int fd;

  while (1) {
    while(client_num < 10) {
       fd = accept(server_socket, (struct sockaddr*)NULL, NULL);
       add_client(fd);
       memset(&client_addr, '0', sizeof(client_addr));
       memset(&clientip, '0', sizeof(clientip));
       getpeername(fd, (struct sockaddr *)&client_addr, &addr_size); 
       strcpy(clientip, inet_ntoa(client_addr.sin_addr));
       printf("\nClient %s :%d connected with socket: %d.\n\n",clientip,(int)ntohs(client_addr.sin_port),fd);

       if (flag == 0) {
           pthread_attr_init(&attr_rd);
           if (pthread_create(&tid_rd, &attr_rd, recv_data, NULL)) {
               perror("ERROR: Pthread create error recv_data. Exiting...");
               exit(EXIT_FAILURE);
           }
           flag = 1;
       }
       client_num++;
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
    //print_mcast_group_list();
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

