#include <stdio.h>

/*
   are_arrays_equal()
   Returns 1 if the strings pointed to by str1 and str2 are the same
   Returns 0 otherwise
 */
int are_arrays_equal(char* str1, char* str2)
{
    size_t i = 0;
    while ( *(str1 + i) == *(str2 + i) && *(str1 + i) != 0)
        i++;
    return *(str1 + i) == *(str2 + i);
}
