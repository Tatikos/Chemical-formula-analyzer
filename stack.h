/**
 * @file stack.h
 * @brief Header file for stack management functions.
 * @author George Fotiou
 * @since 29/10/2024
 * This header file declares functions for managing a stack of strings,
 * including operations to push, pop, peek, and check if the stack is empty.
 */

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Pushes a string onto the stack, expanding the array if necessary.
 * 
 * This function adds a new string to the stack and increases its capacity if it is full.
 * 
 * @param strArr      Pointer to the array of strings (stack).
 * @param strCount    Pointer to the current number of strings in the stack.
 * @param strCapacity Pointer to the current capacity of the stack.
 * @param str         The string to push onto the stack.
 * 
 * @return 0 on success, or 1 on failure (memory allocation error).
 */
int pushStr(char ***strArr, int *strCount, int *strCapacity, const char *str);

/**
 * @brief Pops a string from the stack.
 * 
 * This function removes the top string from the stack and returns it. 
 * The caller is responsible for freeing the returned string.
 * 
 * @param arr  Pointer to the array of strings (stack).
 * @param size Pointer to the current size of the stack.
 * 
 * @return Pointer to the popped string, or NULL if the stack is empty.
 */
char *popstr(char **arr, int *size);

/**
 * @brief Peeks at the top string of the stack without removing it.
 * 
 * This function returns the top string from the stack without modifying the stack.
 * 
 * @param arr  Pointer to the array of strings (stack).
 * @param size Current size of the stack.
 * 
 * @return Pointer to the top string, or NULL if the stack is empty.
 */
char *peek(char **arr, int size);

/**
 * @brief Checks if the stack is empty.
 * 
 * This function checks if there are any elements in the stack.
 * 
 * @param size Current size of the stack.
 * 
 * @return 1 if the stack is empty, 0 otherwise.
 */
int stackisempty(int size);

#endif
