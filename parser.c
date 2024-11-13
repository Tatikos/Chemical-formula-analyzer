/**
 * @file parser.c
 * @brief Implements functions for processing chemical formulas, balancing checks, and proton calculations.
 * @author George Fotiou
 * @since 29/10/2024
 * This source file includes implementations for handling and analyzing chemical formulas,
 * calculating proton counts, ensuring chemical balance, and various utility functions.
 */

#include "parser.h"
#include "stack.h"
#include "data.h"
#include <ctype.h>

/**
 * @brief Calculates the number of protons in a given element or compound.
 * 
 * @param stringpegke  The string representation of the element or compound.
 * @param intArr       Array holding atomic data.
 * @param strArr       Array of strings for element names.
 * @param strCount     Count of elements in strArr.
 * 
 * @return The number of protons for the element or compound.
 */
int calculateprotons(char *stringpegke, short *intArr, char **strArr, char strCount) {
    int sum = 0;
    for (int j = 0; j < strCount; j++) {
        if (strcmp(stringpegke, strArr[j]) == 0) {
            sum = intArr[j];
            return sum;
        }
    }
    return sum;
}

/**
 * @brief Checks if a chemical formula is balanced by matching parentheses.
 * 
 * @param str Input string representing the formula.
 * 
 * @return 1 if the formula is balanced, 0 otherwise.
 */
int isBalanced(const char *str) {
    int length = strlen(str);
    char *stack = (char *)malloc(length * sizeof(char));
    if (stack == NULL) {
        perror("Error allocating memory for stack\n");
        return 0;
    }
    int top = -1;

    for (int i = 0; i < length; i++) {
        if (str[i] == '(') {
            stack[++top] = str[i];
        } else if (str[i] == ')') {
            if (top == -1) {
                free(stack);
                return 0;
            }
            top--;
        }
    }

    int balanced = (top == -1);
    free(stack);
    return balanced;
}

/**
 * @brief Processes a formula string, calculating proton counts and managing output.
 * 
 * @param formula       The formula to process.
 * @param intArr        Array containing atomic data.
 * @param strArr        Array of element names.
 * @param strCount      Number of elements in strArr.
 * @param flag          Mode flag for processing.
 * @param outputFile    Path to the output file for results.
 */
void processtype(char *formula, short *intArr, char **strArr, char strCount, char *flag, char *outputFile) {
    FILE *fp2 = NULL;
    if (strcmp(flag, "-ext") == 0 || strcmp(flag, "-pn") == 0) {
        fp2 = fopen(outputFile, "a+");
        if (fp2 == NULL) {
            perror("Unable to open file");
            exit(1);
        }
    }

    int stackCapacity = 1000;
    char **stack = (char **)malloc(stackCapacity * sizeof(char *));
    int top = 0;

    char *result = (char *)malloc(5000 * sizeof(char)); 
    *result = '\0';

    int totalProtons = 0;
    int formula_len = strlen(formula);
    int formulaCapacity = formula_len;
    char **formulaStack = (char **)malloc(formulaCapacity * sizeof(char *));
    int formulaTop = 0;

    // Parsing the formula from the end to the beginning
    for (int i = formula_len - 1; i >= 0; i--) {
        if (isdigit(formula[i])) {
            int start = i;
            while (i >= 0 && isdigit(formula[i])) {
                i--;
            }
            i++;
            int numLen = start - i + 1;
            char *numberStr = (char *)malloc((numLen + 1) * sizeof(char));
            strncpy(numberStr, &formula[i], numLen);
            numberStr[numLen] = '\0';
            pushStr(&formulaStack, &formulaTop, &formulaCapacity, numberStr);
        } else {
            char temp[3] = {formula[i], '\0', '\0'};
            if (isalpha(formula[i]) && i > 0 && islower(formula[i])) {
                temp[0] = formula[i - 1];
                temp[1] = formula[i];
                i--;
            }
            pushStr(&formulaStack, &formulaTop, &formulaCapacity, strdup(temp));
        }
    }

    while (!stackisempty(formulaTop)) {
        char *item = popstr(formulaStack, &formulaTop);

        if (isalpha(item[0])) {  
            pushStr(&stack, &top, &stackCapacity, item);  
        } else if (isdigit(item[0])) {
            int multiplier = atoi(item);
            char *temp = popstr(stack, &top);

            for (int j = 0; j < multiplier; j++) {
                pushStr(&stack, &top, &stackCapacity, temp);
            }
            free(temp);
        } else if (strcmp(item, "(") == 0) {
            pushStr(&stack, &top, &stackCapacity, "(");
        } else if (strcmp(item, ")") == 0) {
            int groupCapacity = 1000;
            char **group = (char **)malloc(groupCapacity * sizeof(char *));
            int group_top = 0;

            while (strcmp(peek(stack, top), "(") != 0) {
                pushStr(&group, &group_top, &groupCapacity, popstr(stack, &top));
            }
            popstr(stack, &top);

            int multiplier = 1;
            if (!stackisempty(formulaTop)) {
                char *next = peek(formulaStack, formulaTop);
                if (isdigit(next[0])) {
                    multiplier = atoi(popstr(formulaStack, &formulaTop));
                }
            }

            for (int j = 0; j < multiplier; j++) {
                for (int k = group_top - 1; k >= 0; k--) {
                    pushStr(&stack, &top, &stackCapacity, group[k]);
                }
            }
            for (int k = 0; k < group_top; k++) {
                free(group[k]);
            }
            free(group);
        }
        free(item);
    }

    for (int j = 0; j < top; j++) {
        strcat(result, stack[j]);
        strcat(result, " ");
        
        int elementProtons = calculateprotons(stack[j], intArr, strArr, strCount);
        totalProtons += elementProtons;

        free(stack[j]);
    }

    if (strcmp(flag, "-ext") == 0) {
        fprintf(fp2, "%s\n", result);
    } else if (strcmp(flag, "-pn") == 0) {
        fprintf(fp2, "%d\n", totalProtons);
    }
    fflush(fp2);
    fclose(fp2);
    free(result);
    free(stack);
    free(formulaStack);
}

/**
 * @brief Extends types and processes input data.
 * 
 * @param intArr       Pointer to an array of atomic data.
 * @param strArr       Pointer to an array of element names.
 * @param strcapacity  Capacity of strArr.
 * @param flag         Processing mode flag.
 * @param inputFile    Input file for reading.
 * @param outputFile   Output file path for results.
 */
void extentedtype(short **intArr, char ***strArr, int strcapacity, char *flag, FILE *inputFile, char *outputFile) {
    int strCount = 0;
    int strCapacity = strcapacity;
    int count = 0;
    char stringpegke3[100];
    char **stringpegke = (char **)malloc(strCapacity * sizeof(char *));
    char str[100];

    if (inputFile == NULL) {
        perror("Unable to open file");
        exit(1);
    }

    while (fscanf(inputFile, "%s", str) == 1) {
        stringpegke3[0] = '\0';
        for (int i = 0; i < strlen(str); i++) {
            if (str[i] == '(' || str[i] == ')') { 
                count++;
                char temp[2] = {str[i], '\0'};
                pushStr(&stringpegke, &strCount, &strCapacity, temp);
            } else if (isdigit(str[i]) && isdigit(str[i + 1])) {
                char temp[3] = {str[i], str[i + 1], '\0'};
                pushStr(&stringpegke, &strCount, &strCapacity, temp);
                i++;
            } else if (isdigit(str[i])) {
                char temp[2] = {str[i], '\0'};
                pushStr(&stringpegke, &strCount, &strCapacity, temp);
            } else {
                int matched = 0;
                int b = 3;
                matchAndPush(&stringpegke, &strCount, &strCapacity, str, &i, strArr, strcapacity, &matched, b);
                if (!matched) {
                    b = 2;
                    matchAndPush(&stringpegke, &strCount, &strCapacity, str, &i, strArr, strcapacity, &matched, b);
                }
                if (!matched) {
                    b = 1;
                    matchAndPush(&stringpegke, &strCount, &strCapacity, str, &i, strArr, strcapacity, &matched, b);
                }
            }
        }
        for (int i = 0; i < strCount; i++) {
            strcat(stringpegke3, stringpegke[i]);
        }
        processtype(stringpegke3, *intArr, *strArr, strcapacity, flag, outputFile);
        for (int i = 0; i < strCount; i++) {
            free(stringpegke[i]);
        }
        strCount = 0;
    }
    fclose(inputFile);
}

/**
 * @brief Matches and pushes elements into the stack.
 * 
 * @param stringpegke  Stack of strings.
 * @param strCount     Count of elements in the stack.
 * @param strCapacity  Stack capacity.
 * @param str          Input string.
 * @param i            Current index in input string.
 * @param strArr       Array of element names.
 * @param strcapacity  Number of elements in strArr.
 * @param matched      Flag indicating if match was found.
 * @param b            Length of substring to match.
 */
void matchAndPush(char ***stringpegke, int *strCount, int *strCapacity, const char *str, int *i, char ***strArr, int strcapacity, int *matched, int b) {
    for (int j = 0; j < strcapacity; j++) {
        if (*i + b - 1 < strlen(str) && strlen((*strArr)[j]) == b && strncmp(&str[*i], (*strArr)[j], b) == 0) {
            *i += b - 1;
            pushStr(stringpegke, strCount, strCapacity, (*strArr)[j]);
            *matched = 1;
            break;
        }
    }
}
