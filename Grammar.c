#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *input; // Input string

// Function declarations
int expr();
int term();
int factor();

// Function to consume the next character from the input
char consume() {
    return *input++;
}

// Function to check if a character is a digit
int isDigit(char c) {
    return isdigit(c);
}

// Function to check if a character is an operator (+, -, *, /)
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to check if a character is a whitespace character
int isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

// Function to skip whitespace characters
void skipWhitespace() {
    while (isWhitespace(*input)) {
        consume();
    }
}

// Function to parse an expression
int expr() {
    int result = term();
    while (isOperator(*input) && (*input == '+' || *input == '-')) {
        char op = consume();
        int nextTerm = term();
        if (op == '+') {
            result += nextTerm;
        } else {
            result -= nextTerm;
        }
    }
    return result;
}

// Function to parse a term
int term() {
    int result = factor();
    while (isOperator(*input) && (*input == '*' || *input == '/')) {
        char op = consume();
        int nextFactor = factor();
        if (op == '*') {
            result *= nextFactor;
        } else {
            if (nextFactor == 0) {
                printf("Error: Division by zero.\n");
                exit(1);
            }
            result /= nextFactor;
        }
    }
    return result;
}

// Function to parse a factor
int factor() {
    skipWhitespace();
    if (isDigit(*input)) {
        int value = 0;
        while (isDigit(*input)) {
            value = value * 10 + (*input - '0');
            consume();
        }
        return value;
    } else if (*input == '(') {
        consume(); // Consume '('
        int result = expr();
        if (*input == ')') {
            consume(); // Consume ')'
            return result;
        } else {
            printf("Error: Expected ')' but found '%c'\n", *input);
            exit(1);
        }
    } else {
        printf("Error: Unexpected character '%c'\n", *input);
        exit(1);
    }
}

// Function to check if the input string satisfies the grammar
int checkGrammar(char *str) {
    input = str;
    int result = expr();
    skipWhitespace();
    if (*input != '\0') {
        printf("Error: Unexpected characters at the end of the input.\n");
        return 0;
    }
    return result;
}

int main() {
    char inputString[100];
    printf("Enter an arithmetic expression: ");
    fgets(inputString, sizeof(inputString), stdin);

    // Remove trailing newline character if present
    if (inputString[strlen(inputString) - 1] == '\n') {
        inputString[strlen(inputString) - 1] = '\0';
    }

    int result = checkGrammar(inputString);
    if (result != 0) {
        printf("The input string satisfies the grammar. Result: %d\n", result);
    } else {
        printf("The input string does not satisfy the grammar.\n");
    }

    return 0;
}
