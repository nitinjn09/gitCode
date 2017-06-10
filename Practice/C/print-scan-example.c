#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/* Note: this is a minimal printf implementation */
/* This is for building understanding only */
int print (char * str, ...)
{
  va_list vl;
  int i = 0, j=0;
  char buff[100]={0}, tmp[20];
  va_start( vl, str );

  while (str && str[i])
  {
    if(str[i] == '%'){
      i++;
      switch (str[i]) {
        case 'c':
          buff[j] = (char)va_arg( vl, int );
          j++;
          break;
        case 'd':
          itoa(va_arg( vl, int ), tmp, 10);
          strcpy(&buff[j], tmp);
          j += strlen(tmp);
          break;
        case 'x':
          itoa(va_arg( vl, int ), tmp, 16);
          strcpy(&buff[j], tmp);
          j += strlen(tmp);
          break;
      }
    } else {
      buff[j] =str[i];
      j++;
    }
    i++;
  } 
  fwrite(buff, j, 1, stdout); 
  va_end(vl);
  return j;
}



/* Note: this is a minimal scanf implementation */
 /* This is for building understanding only */
 
int scan (char * str, ...)
 {
   va_list vl;
   int i = 0, j=0, ret = 0;
   char buff[100] = {0}, tmp[20], c;
   char *out_loc;
   while(c != ',') {
     if (fread(&c, 1, 1, stdin)) {
       buff[i] = c;
       i++;
     }
   }
   va_start( vl, str );
   i = 0;
   while (str && str[i])
   {
     if (str[i] == '%') {
       i++;
       switch (str[i]) {
         case 'c': {
           *(char *)va_arg( vl, char* ) = buff[j];
           j++;
           ret ++;
           break;
         }
         case 'd': {
           *(int *)va_arg( vl, int* ) =strtol(&buff[j], &out_loc, 10);
           j+=out_loc -&buff[j];
           ret++;
           break;
         }
         case 'x': {
           *(int *)va_arg( vl, int* ) =strtol(&buff[j], &out_loc, 16);
           j+=out_loc -&buff[j];
           ret++;
           break;
         }
       }
     } else {
       buff[j] =str[i];
       j++;
     }
     i++;
   }
   va_end(vl);
   return ret;
 
 }
 int main(int argc, char *argv[])
 
 {
   char c;
   int i;
   int h;
   int ret = 0;
   ret = scan("%c %d %x", &c, &i, &h);
   print("C = %c, I = %d, H = %X, Return %d", c, i, h, ret);
   return 0;
 }
