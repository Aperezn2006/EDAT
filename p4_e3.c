#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bstree.h"
#include "types.h"
#include "search_queue.h"
#include "file_utils.h"

#define MAX_LINE 1000

int main (int argc, char const *argv[]){
    FILE *f_in = NULL;
    SearchQueue *sq = NULL;
    char line [MAX_LINE];
    int line_count = 0, i = 0, n;
    float sum = 0.0;
    int count = 0;
    float *data = NULL;
    float *grades = NULL;

    if (argc != 2) {
        printf("Usage: %s input_file \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (!(f_in = fopen(argv[1], "r"))) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    n =  atoi(fgets(line, MAX_LINE, f_in));

    if (!(sq = search_queue_new(float_print, float_cmp))) { 
        fclose(f_in);
        printf("Failed to initialize search queue.\n");
        exit(EXIT_FAILURE);
    }

    grades = malloc(n * sizeof(float));

    while (fgets(line, MAX_LINE, f_in)) {
        grades[line_count] = atof(line); 
        

        if (search_queue_push(sq, &(grades[line_count])) == ERROR) {
            free (grades);
            fclose(f_in);
            search_queue_free(sq);
            exit(EXIT_FAILURE);
        }

        line_count++;
    }

    fclose(f_in);

    /*SALIDA*/
    printf ("\n");
    printf ("Ordered grades: ");
    search_queue_print (stdout, sq);
    printf ("\n");

    while ((data = search_queue_pop(sq)) != NULL) {
        sum += *data;
        count++;
    }
    while (i<n) {
        search_queue_push (sq, &grades[i]);
        i++;
    }

    printf("Mean: %.2f\n\n", sum / count);

    printf("Median: ");

    if (n%2 == 0){
        for (i=0; i < (n/2); i++){
            search_queue_pop (sq);
        }
        printf ("%.2f", (*(float *)search_queue_pop (sq) + *(float *)search_queue_pop (sq))/2.0); 
    } else {
        for (i=0; i < ((n/2)+0.5); i++){
            search_queue_pop (sq);
        }
        printf ("%.2f", *(float *)search_queue_pop (sq)); 

    }

    i = 0;
    while (i<n) {
        search_queue_push (sq, &grades[i]);
        i++;
    }
    
    printf ("\n\n");

    printf ("Lowest grades: ");
    printf ("%.2f ", *(float *)search_queue_pop(sq));
    printf ("%.2f ", *(float *)search_queue_pop(sq));
    printf ("%.2f \n", *(float *)search_queue_pop(sq));
    printf ("\n");

    printf ("Highest grades: ");
    printf ("%.2f ", *(float *)search_queue_getBack(sq));
    tree_remove (search_queue_get_tree(sq), search_queue_getBack(sq));
    printf ("%.2f ", *(float *)search_queue_getBack(sq));
    tree_remove (search_queue_get_tree(sq), search_queue_getBack(sq));
    printf ("%.2f ", *(float *)search_queue_getBack(sq));
    tree_remove (search_queue_get_tree(sq), search_queue_getBack(sq));
    printf ("\n");

    exit(EXIT_SUCCESS);
}
