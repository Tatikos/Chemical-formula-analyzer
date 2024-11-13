/**
 * @file main.c
 * @brief Main entry point for the chemical formula processing program.
 * @author George Fotiou
 * @since 29/10/2024
 * This file contains the main entry point for the chemical formula processing program.
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "parser.h"

/**
 * @brief Main entry point of the program.
 * 
 * This program processes a periodic table and computes various properties 
 * of chemical formulas based on user-specified flags. It can compute total 
 * proton numbers, generate extended versions of formulas, or verify balanced 
 * parentheses in chemical formulas.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * 
 * @return 0 on success, or 1 on failure.
 */
int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc < 5) {
        fprintf(stderr, "Usage: %s <periodicTable.txt> [-pn|-ext|-v] <input.txt> <output.txt>\n", argv[0]);
        return 1; // Return error if insufficient arguments
    }

    char *periodicTableFile = argv[1];  ///< Path to the periodic table file
    char *flag = argv[2];                 ///< Operation flag: -pn, -ext, or -v
    char *inputFile = argv[3];            ///< Path to the input file with chemical formulas
    char *outputFile = argv[4];           ///< Path to the output file for results

    // Open the input files and check for errors
    FILE *input = fopen(inputFile, "r");
    FILE *periodicTable = fopen(periodicTableFile, "r");
    if (!input || !periodicTable) {
        perror("File error");
        return 1; // Return error if files cannot be opened
    }

    short *intArr = NULL;  ///< Array for storing integer values (proton numbers)
    char **strArr = NULL;  ///< Array for storing string values (element symbols)
    int intSize = 0;       ///< Count of integers read from the periodic table
    int strSize = 0;       ///< Count of strings read from the periodic table

    // Read the data from the periodic table file
    if (readData(periodicTable, &intArr, &strArr, &intSize, &strSize) != 0) {
        return 1; // Return error if data reading fails
    }

    // Process based on the specified flag
    if (strcmp(flag, "-pn") == 0) {
        printf("Compute total proton number of formulas in %s\n", inputFile);
        extentedtype(&intArr, &strArr, strSize, flag, input, outputFile);
        printf("Writing formulas to %s\n", outputFile);
    } else if (strcmp(flag, "-ext") == 0) {
        printf("Compute extended version of formulas in %s\n", inputFile);
        extentedtype(&intArr, &strArr, strSize, flag, input, outputFile);
        printf("Writing formulas to %s\n", outputFile);
    } else if (strcmp(flag, "-v") == 0) {
        printf("Verify balanced parentheses in %s\n", inputFile);
        int lineNumber = 1, i = 0;   ///< Current line number in the input file
        char formula[100];    ///< Buffer for reading formulas

        // Read and verify each formula from the input file
        while (fscanf(input, "%s", formula) == 1) {
            if (isBalanced(formula) == 0) {
                printf("Error: Unbalanced parenthesis at line %d\n", lineNumber);
            }
            lineNumber++; // Increment line number
            formula[0] = '\0'; // Clear the buffer
        }
        if(i==0)
            printf("Parentheses are balanced for all chemical formulas\n");
    } else {
        // Handle unknown flags
        fprintf(stderr, "Unknown flag: %s\n", flag);
        return 1; // Return error for unknown flag
    }
    free(intArr);
    free(strArr);
    return 0; // Return success
}
