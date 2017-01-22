#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pi_calc.h>
#include <sys/time.h>

#define SEARCH_SIZE 1000000
#define BUFFER_SIZE 10000

int main() {
    pi_calc_handler* handler = pi_calc_init();
    int s = SEARCH_SIZE;
    //24 3F 6A 88 85 A3
    const char* needle = "cats";// { 0x24, 0x3f, 0x6a, 0x88, 0x85, 0xa3, 0 };
    char buffer[BUFFER_SIZE];

    unsigned long int pos = 0;

    struct timeval start, end;

    gettimeofday(&start, NULL);

    while(s-- > 0){
        char c = pi_calc_next_char( handler );

        if( pos < BUFFER_SIZE ) {
            buffer[pos++] = c;
        } else {
            gettimeofday(&end, NULL);
            printf( "buffer full, took: %ld seconds.\n", end.tv_sec - start.tv_sec );
            gettimeofday(&start, NULL);
            char* ptr = strstr( buffer, needle );
            if( ptr != NULL ) {
                printf( "I found: %s.\n", needle );
            }
            pos = 0;
        }
    }

    pi_calc_free( handler );
    return 0;
}