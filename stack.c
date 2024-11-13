/**
 * @file stack.c
 * @brief Implements functions for managing a stack of strings.
 * @author George Fotiou
 * @since 29/10/2024
 * This source file includes implementations for managing a dynamically allocated stack of strings,
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#define STACK_SIZE 1000

/**
 * @brief Structure representing a stack for storing string elements.
 */
typedef struct {
    char items[STACK_SIZE][10]; /**< Array to store stack items. */
    int top; /**< The current top of the stack. */
} Stack;

/**
 * @brief Checks if the stack is empty.
 * 
 * This function checks if the number of elements in the stack is zero.
 * 
 * @param size Current size of the stack.
 * 
 * @return 1 if the stack is empty, 0 otherwise.
 */
int stackisempty(int size) {
    return size == 0; // Return true if size is zero
}

/**
 * @brief Pushes a string onto the stack, expanding the array if necessary.
 * 
 * This function adds a new string to the stack. If the stack is full, it reallocates
 * memory to accommodate more strings.
 * 
 * @param strArr      Pointer to the array of strings (stack).
 * @param strCount    Pointer to the current number of strings in the stack.
 * @param strCapacity Pointer to the current capacity of the stack.
 * @param str         The string to push onto the stack.
 * 
 * @return 0 on success, or 1 on failure (memory allocation error).
 */
int pushStr(char ***strArr, int *strCount, int *strCapacity, const char *str) {
    // Check if reallocation is needed
    if (*strCount >= *strCapacity) {
        *strCapacity *= 2; // Double the capacity
        char **temp = (char **)realloc(*strArr, *strCapacity * sizeof(char *));
        if (temp == NULL) { 
            perror("Error reallocating memory for strings");
            return 1; // Return error if realloc fails
        }
        *strArr = temp; // Update the pointer
    }

    // Allocate memory for the new string and check for success
    (*strArr)[*strCount] = (char *)malloc((strlen(str) + 1) * sizeof(char));
    if ((*strArr)[*strCount] == NULL) {
        perror("Error allocating memory for string");
        return 1; // Return error if malloc fails
    }

    // Copy the string and update the count
    strcpy((*strArr)[(*strCount)++], str);
    return 0; // Return success
}

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
char *popstr(char **arr, int *size) {
    if (*size == 0) {
        perror("Error: stack is empty");
        exit(1); // Exit if trying to pop from an empty stack
    }
    char *popped = arr[--(*size)]; // Decrement size and return top element
    return popped; // Return the popped string
}

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
char *peek(char **arr, int size) {
    if (size == 0) {
        perror("Error: stack is empty");
        exit(1); // Exit if trying to peek at an empty stack
    }
    return arr[size - 1]; // Return the top string without modifying the stack
}
