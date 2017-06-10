#include <stdio.h>
#include <time.h>

int main()
{
    time_t t;
    char buffer[26];
    struct tm* tm_info;

    time(&t);
    tm_info = localtime(&t);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    puts(buffer);

    return 0;
}
