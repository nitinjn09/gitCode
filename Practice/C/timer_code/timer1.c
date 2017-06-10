#include <time.h>
#include <stdio.h>

int main() {
    int program_done = 0;
    time_t start = time(NULL);
    while(1) {
        if (time(NULL) - start >= 5) {
            start = start + 5;
            printf("Nitin\n");
            // insert periodic stuff here
        }
        // do small pieces of work here, no longer than the timer limit.
        // if no work to do, a sleep(1) could be placed here.
        if (program_done) break;
    }
}
