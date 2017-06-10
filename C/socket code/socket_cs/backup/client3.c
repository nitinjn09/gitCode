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

/*
Recieved data formate: <mcast_group>#<data_type>#<Data>

Sent data formate: <mcast_group>#<data_type>/<data>
*/

int mcast_group, type_of_data;
int sockfd;  //server socket

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
       mcast_group = atoi(&recvBuff[i]);
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


/* Function to recieve data from server */
void *recv_data()
{
  char recvBuff[1024], buffer[1024], timeBuff[40];
   
  printf("I am in recv_data function\n");
  while(1) { 
    memset(buffer, '0',sizeof(buffer));
    memset(timeBuff, '0', sizeof(timeBuff));
    memset(recvBuff, '0',sizeof(recvBuff));
    /* Now read server response */ 
    if (read(sockfd, recvBuff, sizeof(recvBuff)) < 0) {
        perror("ERROR reading from socket");
        exit(EXIT_FAILURE);
    }
    analyze_data(recvBuff, timeBuff, buffer);
    printf("Server: %s: mcast_group: %d, type_of_data: %d, Data: %s\n",timeBuff, mcast_group, type_of_data, buffer); 
    sleep(1);
  }
}


/* Function to send data to server */
void *send_data()
{
  time_t ticks;
  char sendBuff[1024];

  while(1) {
    memset(sendBuff, '0',sizeof(sendBuff));
    ticks = time(NULL);
    //fgets(sendBuff,255,stdin);
    snprintf(sendBuff, sizeof(sendBuff), "%.24s\r#%d#%d#Client says Hi..",ctime(&ticks), mcast_group, type_of_data);
    /* Send message to the server */
    if (write(sockfd, sendBuff, sizeof(sendBuff)) < 0) {
        perror("ERROR writing to socket");
        printf("Nitin-4\n");
        exit(EXIT_FAILURE);
    }
    sleep(1);
  }
}




int main(int argc, char *argv[])
{
    struct sockaddr_in serv_addr; 
    pthread_t tid_rd, tid_sd;
    pthread_attr_t attr_rd, attr_sd;

    if(argc != 2) {
       printf("\n Usage: %s <ip of server> \n",argv[0]);
       return 1;
    }
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0) {
       perror("inet_pton error occured");
       return 1;
    }
    /* Connect to server sockets */
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connect to server socket");
        exit(EXIT_FAILURE);
    } 

    pthread_attr_init(&attr_sd);
    if (pthread_create(&tid_sd, &attr_sd, send_data, NULL)) {
        printf("\nERROR: Pthread create error send_data. Exiting...");
        exit(EXIT_FAILURE);
    }
    printf("send_data thread created\n");
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
