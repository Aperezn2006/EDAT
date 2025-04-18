#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bstree.h"
#include "types.h"
#include "search_queue.h"
#include "file_utils.h"

#define MAX_LINE 1000

int getNumberLines(FILE *pf);

int main (int argc, char const *argv[]){
    FILE *f_in = NULL, *f_out = NULL;
    char line [MAX_LINE];
    SearchQueue *sq = NULL;
    int line_count = 0, i, n;
    char **line_copy;

    if (argc != 3) {
        printf("Usage: %s input_file output_file \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if (!(f_in = fopen(argv[1], "r"))) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    n = getNumberLines (f_in);
    rewind (f_in);
    
    if (!(sq = search_queue_new(string_print, string_cmp))) { 
        fclose(f_in);
        printf("Failed to initialize search queue.\n");
        exit(EXIT_FAILURE);
    }

    line_copy = malloc(n * sizeof(char *));

    while (fgets(line, MAX_LINE, f_in)) {
        line_copy[line_count] = aux_strdup(line);
        if (!line_copy[line_count]) {
            for (i=0; i < line_count; i++){
                free (line_copy[i]);
            }
            free(line_copy);
            fclose(f_in);
            search_queue_free(sq);
            exit(EXIT_FAILURE);
        }

        if (search_queue_push(sq, line_copy[line_count]) == ERROR) {
            for (i=0; i < line_count; i++){
                free (line_copy[i]);
            }
            free(line_copy);
            fclose(f_in);
            search_queue_free(sq);
            exit(EXIT_FAILURE);
        }

        line_count++;
    }
    fclose(f_in);

    if (!(f_out = fopen(argv[2], "w"))) {
        for (i=0; i < line_count; i++){
            free (line_copy[i]);
        }
        perror("Failed to open output file");
        search_queue_free(sq);
        exit(EXIT_FAILURE);
    }

    if (search_queue_print(f_out, sq) == ERROR) {
        for (i=0; i < line_count; i++){
            free (line_copy[i]);
        }
        free(line_copy);
        fclose(f_out);
        search_queue_free(sq);
        exit(EXIT_FAILURE);
    }

    for (i=0; i < line_count; i++){
        free (line_copy[i]);
    }
    free(line_copy);
    fclose(f_out);
    search_queue_free(sq);
    exit(EXIT_SUCCESS);
}

int getNumberLines(FILE *pf){
    char line[MAX_LINE];
    int n = 0;

    while (fgets(line, MAX_LINE, pf) != NULL) {
      n++;
    }

    return n;
}