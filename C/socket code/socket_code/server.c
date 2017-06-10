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
Recieved data formate: <time>#<num_of_group>#<mcast_groups>#<data_type>#<data>
Sent data formate: <time>#<data_seq_num>#<data_type>#<data>  // proposed
<time>#<mcast_group>#<data_type>/<data>   //current

type of data:  1. registration request
               2. 
               3. 
*/

#define PACKET_SIZE 1024

typedef struct server_input_st_
{   
    int task_id;
    int task_type; 
    int packet_seq_num;
    int input_len;
    int input_data_to_client[PACKET_SIZE];
    int task_result;
}input_st;

typedef struct clinet_list
{
  int  client_fd;  
  struct client_list *next;
}client_list;


int data_sent;
int data_seq_num;
int server_socket;
int type_of_data;                
int client_num;  
int pos;

client_list *cl_head = NULL;

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
    return;
  }
  while(temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = node;
  return;
}

void *recv_data()
{
  client_list *temp = cl_head;
  input_st *data;

  while(1) {
   if (data_sent) {
    if (cl_head == NULL) {
       printf("No data to read from clients\n");
       sleep(1);
    }
    else {
      data = (input_st*) malloc(sizeof(input_st));
      temp = cl_head;
      while(temp != NULL) {
        if (recv(temp->client_fd, (void*)data,sizeof(input_st), MSG_PEEK | MSG_DONTWAIT) < 0) {
            perror("ERROR reading from socket");
          }
          printf("task_id %d, task_type %d\n",data->task_id, data->task_type);
          fflush(stdout);
          temp = temp->next;
      }
      free(data);
    }
    data_sent--;
  }
  
  sleep(1);
  }
}

void send_data()
{
  input_st *data;
  client_list *temp;
  
  signal(SIGPIPE,SIG_IGN);

    if (cl_head == NULL) {
      printf("No client connected yet to send any data\n");
    }
    else {
      temp = cl_head;
      while (temp != NULL) {
        data = (input_st*) malloc(sizeof(input_st));
          data->task_id = 1;
          data->task_type = 2;
          
        /* Write a response to the client */
        
        if (send(temp->client_fd,(void*) data, sizeof(input_st), 0) < 0) {
            perror("ERROR writing to socket");
        }
        temp = temp->next;
        data_sent++;
        free(data);
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


void set_server_socket()
{
  struct sockaddr_in serv_addr;
  struct ifaddrs *if_addr, *tmp;

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

}

int main(int argc, char *argv[])
{
  
  int choice;
  pthread_t tid_sd, tid_acc;
  pthread_attr_t attr_sd, attr_acc;

  set_server_socket();
  
  pthread_attr_init(&attr_acc);
  if (pthread_create(&tid_acc, &attr_acc, accept_clients_connection, NULL)) {
      printf("\nERROR: Pthread create error accept_clients_connection. Exiting...");
      exit(EXIT_FAILURE);
  }
  
  printf("\nEnter your choice:: \n 0. Exit \n 1. Send data to client \n"
      " 2. Print client list\n");
  while(1) {
    scanf("%d", &choice);

    switch(choice) {

      case 1: send_data();
      break;

      case 2: print_client_list();
      break;

      case 0: exit(1);

      default: printf("\n Invalid choice. Enter again\n");
      break;
    }
  }
  return 0;
}

