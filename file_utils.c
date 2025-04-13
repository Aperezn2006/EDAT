/**
 * @file  file_utils.c
 * @author Izan Robles
 * @brief Utils for different datatypes
 */


 #include "file_utils.h"

 /* -----------------------------------------  FLOAT  ----------------------------------------- */
 
 int _float_print(FILE *pf, const void *a)
 {
     if (!pf || !a)
         return -1;
     return fprintf(pf, "%.2f", *(float *)a);
 }
 
 int float_cmp(const void *a, const void *b)
 {
     float fa;
     float fb;
 
     if (!a || !b)
     {
         return -2;
     }
 
     fa = *(float *)a;
     fb = *(float *)b;
 
     if (fa > fb)
     {
         return 1;
     }
     else if (fa < fb)
     {
         return -1;
     }
     else
     {
         return 0;
     }
 }