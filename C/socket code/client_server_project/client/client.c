#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int i, status;
  int clientSocket=0;
char buffer[256] = "";

/*
* Client application specific code goes here
* e.g. receive messages from server, respond, etc.
* Receive and respond until server stops sending messages
*/

while (0 < (status = read(clientSocket, buffer, sizeof(buffer))))
  {
    printf("%s", buffer);
    for (i = 0; i <= 255; i++) buffer[i] = 0;
    fgets(buffer, 256, stdin);
    write(clientSocket, buffer, strlen(buffer));
  }
    close(clientSocket);
    return 0;
  }
