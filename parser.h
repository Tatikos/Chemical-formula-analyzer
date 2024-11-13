/**
 * @file parser.h
 * @brief Header file containing function declarations for processing and analyzing chemical formulas.
 * @author George Fotiou
 * @since 29/10/2024
 * This file provides declarations of functions used to process chemical formulas, calculate protons,
 * check formula balance, match and push elements, extend types, and repeat and append strings.
 */

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Processes a chemical formula and performs operations based on specified parameters.
 * 
 * @param formula      The input chemical formula as a string.
 * @param intArr       Pointer to an array of short integers.
 * @param strArr       Array of strings for storing parsed elements.
 * @param strCount     The count of strings in strArr.
 * @param flag         Pointer to a flag that determines specific processing rules.
 * @param outputFile   Pointer to a string representing the output file path.
 */
void processtype(char *formula, short *intArr, char **strArr, char strCount, char *flag, char *outputFile);

/**
 * @brief Calculates the number of protons for a given element or compound.
 * 
 * @param stringpegke  The input string representing the element or compound.
 * @param intArr       Pointer to an array of short integers representing atomic information.
 * @param strArr       Array of strings with element names.
 * @param strCount     The count of strings in strArr.
 * 
 * @return The total number of protons calculated based on the input string.
 */
int calculateprotons(char *stringpegke, short *intArr, char **strArr, char strCount);

/**
 * @brief Checks if a given chemical formula is balanced.
 * 
 * @param str The input string representing the chemical formula.
 * 
 * @return Non-zero if the formula is balanced; otherwise, zero.
 */
int isBalanced(const char *str);

/**
 * @brief Matches and pushes elements from a formula string to an array, updating relevant counters.
 * 
 * @param stringpegke  Triple pointer to a string for storing parsed formula.
 * @param strCount     Pointer to the current count of strings in the array.
 * @param strCapacity  Pointer to the capacity of the string array.
 * @param str          The input formula string.
 * @param i            Pointer to the current index in the formula string.
 * @param strArr       Triple pointer to the array storing element names.
 * @param strcapacity  The capacity of strArr.
 * @param matched      Pointer to a flag indicating if a match was found.
 * @param b            Additional integer parameter for processing control.
 */
void matchAndPush(char ***stringpegke, int *strCount, int *strCapacity, const char *str, int *i, char ***strArr, int strcapacity, int *matched, int b);

/**
 * @brief Extends types and processes input based on specified flags and files.
 * 
 * @param intArr       Pointer to an array of short integers representing atomic data.
 * @param strArr       Triple pointer to an array of strings for storing element names.
 * @param strcapacity  The capacity of strArr.
 * @param flag         Pointer to a flag determining specific processing options.
 * @param inputFile    File pointer to the input file for processing.
 * @param outputFile   Pointer to a string representing the output file path.
 */
void extentedtype(short **intArr, char ***strArr, int strcapacity, char *flag, FILE *inputFile, char *outputFile);

#endif
