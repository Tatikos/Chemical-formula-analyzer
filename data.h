/**
 * @file data.h
 * @brief Header file for data management functions.
 * @author George Fotiou
 * @since 29/10/2024
 * This header file declares functions for managing integer arrays and reading data 
 * from files into dynamically allocated structures.
 */

#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Pushes a short integer onto an array, expanding the array if necessary.
 * 
 * @param intArr       Pointer to an array of short integers.
 * @param intCount     Pointer to the current number of integers in the array.
 * @param intCapacity  Pointer to the current capacity of the array.
 * @param num          The short integer to push onto the array.
 * 
 * @return 1 if the push was successful, 0 otherwise.
 */
int pushInt(short **intArr, int *intCount, int *intCapacity, short num);

/**
 * @brief Reads data from a file and populates arrays for integers and strings.
 * 
 * @param fp           Pointer to the file stream to read from.
 * @param intArr       Pointer to an array of short integers to populate.
 * @param strArr       Pointer to an array of strings to populate.
 * @param intSize      Pointer to an integer for storing the size of intArr.
 * @param strSize      Pointer to an integer for storing the size of strArr.
 * 
 * @return The number of items read from the file.
 */
int readData(FILE *fp, short **intArr, char ***strArr, int *intSize, int *strSize);

#endif
