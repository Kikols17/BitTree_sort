#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BitTree_sort.h"


int main(int argc, char *argv[]) {
    int *array;
    int next_val;

    if (argc!=3) {
        printf("SHOULD BE:\n\t-> %s <elements> <seed>\n", argv[0]);
        return 1;
    } else {
        printf("Sorting %d elements, with see %d.\n", atoi(argv[1]), atoi(argv[2]));
    }

    array = malloc( atoi(argv[1])*sizeof(int) );
    srand(atoi(argv[2]));


    /* CREATE ARRAY OF RANDOM INTS */
    for (int i=0; i<atoi(argv[1]); ++i) {
        next_val = rand();

        if (rand()%2) {
            next_val *= -1;
        }

        array[i] = next_val;
        //printf("%d ", array[i]);
    }
    //printf("\n");

    /* SORT */
    bittreesort(atoi(argv[1]), array);

    /* PRINT HOPEFULLY SORTED ARRAY */
    for (int i=0; i<atoi(argv[1]); ++i) {
        //printf("%d ", array[i]);
    }
    //printf("\n");


    return 0;
}