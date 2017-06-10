#include <stdio.h>
#include <pthread.h>
int a();
int b();
//static pthread_mutex_t  server_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t  server_mutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER;
int main()
{

    a();
    b();
return 0;
}

int a()
{
    int a =10;
    pthread_mutex_lock(&server_mutex);
        printf("a = %d\n", a);
//     pthread_mutex_unlock(&server_mutex);

     return 0;
}

int b()
{
    int a = 20;
   if(pthread_mutex_lock(&server_mutex) == 0) {
     printf("a = %d\n", a);
      pthread_mutex_unlock(&server_mutex);
   } else {
       printf("\n lock error in b()\n");
   }
      return 0;
}
