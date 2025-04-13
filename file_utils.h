/**
 * @file  file_utils.h
 * @author Izan Robles
 * @brief Utils for different datatypes
 */

 #ifndef FILE_UTILS_H
 #define FILE_UTILS_H
 
 #include <stdlib.h>
 #include <stdio.h>
 
 /* -----------------------------------------  FLOAT  ----------------------------------------- */
 
 /**
  * @brief Prints a float number.
  * @author Izan Robles
  *
  * @param pf file to print float
  * @param a pointer to float to be printed
  * 
  * @return number of elements printed or -1 if an error occured
  **/
 int _float_print(FILE *pf, const void *a);
 
 /**
  * @brief Compares to float numbers.
  * @author Izan Robles
  *
  * @param a pointer to the first float
  * @param b pointer to the second float
  * 
  * @return returns 1 if a > b, -1 if b > a,0 if they are the same or -2 if an error occured
  **/
 int float_cmp(const void *a, const void *b);
 
 #endif