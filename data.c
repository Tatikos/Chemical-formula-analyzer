/**
 * @file data.c
 * @brief Implements functions for managing integer arrays and reading data from files into dynamically allocated structures.
 * @author George Fotiou
 * @since 29/10/2024
 * This source file includes implementations for managing integer arrays and reading data from files into dynamically allocated structures.
 * 
 */

#include "data.h"
#include "stack.h"

/**
 * @brief Pushes a short integer onto an array, expanding the array if necessary.
 * 
 * This function checks if there is enough capacity in the integer array. If not, it 
 * reallocates memory to increase its size. The new number is then added to the array.
 * 
 * @param intArr       Pointer to an array of short integers.
 * @param intCount     Pointer to the current number of integers in the array.
 * @param intCapacity  Pointer to the current capacity of the array.
 * @param num          The short integer to push onto the array.
 * 
 * @return 0 on success, or 1 on failure (memory allocation error).
 */
int pushInt(short **intArr, int *intCount, int *intCapacity, short num) {
    if (*intCount >= *intCapacity) {
        *intCapacity *= 2; 
        *intArr = (short *)realloc(*intArr, *intCapacity * sizeof(short));
        if (*intArr == NULL) {
            perror("Error reallocating memory for integers\n");
            return 1; 
        }
    }
    (*intArr)[(*intCount)++] = num; 
    return 0;
}

/**
 * @brief Reads data from a file and populates arrays for integers and strings.
 * 
 * This function reads pairs of strings and short integers from a file. It populates 
 * the provided integer and string arrays while dynamically managing their memory.
 * 
 * @param fp           Pointer to the file stream to read from.
 * @param intArr       Pointer to an array of short integers to populate.
 * @param strArr       Pointer to an array of strings to populate.
 * @param intSize      Pointer to an integer for storing the size of intArr.
 * @param strSize      Pointer to an integer for storing the size of strArr.
 * 
 * @return 0 on success, or 1 on failure (memory allocation error or read error).
 */
int readData(FILE *fp, short **intArr, char ***strArr, int *intSize, int *strSize) {
    short num;
    char str[100];
    int intCount = 0;
    int strCount = 0;
    int intCapacity = 10; 
    int strCapacity = 10; 

    
    *intArr = (short *)malloc(intCapacity * sizeof(short));
    *strArr = (char **)malloc(strCapacity * sizeof(char *));
    if (*intArr == NULL || *strArr == NULL) {
        perror("Error allocating memory\n");
        return 1; 
    }

   
    while (fscanf(fp, "%s %hd", str, &num) == 2) {
        if (pushInt(intArr, &intCount, &intCapacity, num) != 0) {
            return 1; 
        }
        if (pushStr(strArr, &strCount, &strCapacity, str) != 0) {
            return 1; 
        }
    }
    *intSize = intCount; 
    *strSize = strCount; 

    fclose(fp); 
    return 0;
}
