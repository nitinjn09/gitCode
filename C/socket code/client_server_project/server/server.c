#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
int i, year, age;
char name[256] = "";
char buffer[256] = "";
char null_buffer[256] = "";
    int slaveSocket = 0;

sprintf(buffer, "Please enter your name: ");
write(slaveSocket, buffer, strlen(buffer));
for (i = 0; i <= 255; i++) buffer[i] = 0;
//memset(buffer, '0', sizeof(buffer));

read(slaveSocket, buffer, sizeof(buffer));
strcpy(name, buffer);
sprintf(buffer, "Hi, %sPlease enter your year of birth: ", name);
write(slaveSocket, buffer, strlen(buffer));
for (i = 0; i <= 255; i++) buffer[i] = 0;

read(slaveSocket, buffer, sizeof(buffer));
year = atoi(buffer);
age = 2015 - year;
sprintf(buffer, "Your approximate age is %d.\nEnter q to quit: ", age);
write(slaveSocket, buffer, strlen(buffer));

close(slaveSocket);
exit(0);
}
