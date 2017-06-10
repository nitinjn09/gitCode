#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <time.h>
#include <pthread.h>

typedef struct server_input_st_
{   
    int task_id;
    int task_type; 
    int packet_seq_num;
    int input_len;
    int *input_data_to_client;
    int task_result;
}input_st;

int mcast_group, type_of_data;
int sockfd; 
char mcast_group_list[255];
int num_of_groups;

int data_recieved;
#define PACKET_SIZE 1024



/* Function to recieve data from server */
void *recv_data()
{
  input_st *data;
  
  while(1) {
    if (data_recieved == 0) {
    data = (input_st*) malloc(sizeof(input_st));
    if (recv(sockfd, (void*) data, sizeof(input_st), MSG_PEEK | MSG_DONTWAIT)  < 0) {
        perror("ERROR reading from socket");
    }
    printf("task_id %d, task_type %d\n", data->task_id, data->task_type);
    fflush(stdout);
    free(data);
    data_recieved =1;
   }
    
    sleep(1);
  }
}


/* Function to send data to server */
void *send_data()
{
  input_st *data;

  while(1) {
    if (data_recieved) {
      data  = (input_st*) malloc(sizeof(input_st));
      data->task_type =1;
      data->task_id = 2;
      if (send(sockfd, (void*)data, sizeof(data), 0) < 0) {
          perror("ERROR writing to socket");
      }
      data_recieved = 0;
      free(data);
    }
  sleep(1);
  }
}


void set_client_socket(char *server_ip)
{
  struct sockaddr_in serv_addr;

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error : Could not create socket \n");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 
    if(inet_pton(AF_INET, server_ip, &serv_addr.sin_addr)<=0) {
       perror("inet_pton error occured");
       exit(EXIT_FAILURE);
    }
    /* Connect to server sockets */
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connect to server socket");
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char *argv[])
{
     
    pthread_t tid_rd, tid_sd;
    pthread_attr_t attr_rd, attr_sd;

    set_client_socket("127.0.0.1");

    pthread_attr_init(&attr_sd);
    if (pthread_create(&tid_sd, &attr_sd, send_data, NULL)) {
        printf("\nERROR: Pthread create error send_data. Exiting...");
        exit(EXIT_FAILURE);
    }

    pthread_attr_init(&attr_rd);
    if (pthread_create(&tid_rd, &attr_rd, recv_data, NULL)) {
        printf("\nERROR: Pthread create error recv_data. Exiting...");
        exit(EXIT_FAILURE);
    }
    
    while(1) {
      sleep(5);
    }    
return 0;
}
