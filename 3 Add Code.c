#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_EXPR_SIZE 100

typedef struct {
    char data[MAX_EXPR_SIZE];
    int top;
} Stack;

void push(Stack *stack, char item) {
    if (stack->top == MAX_EXPR_SIZE - 1) {
        printf("Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->data[++stack->top] = item;
}

char pop(Stack *stack) {
    if (stack->top == -1) {
        printf("Error: Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }
}

void infixToPostfix(char *infix, char *postfix) {
    Stack stack;
    stack.top = -1;
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        char ch = infix[i];
        if (isdigit(ch)) {
            postfix[j++] = ch;
        } else if (isOperator(ch)) {
            while (stack.top != -1 && precedence(stack.data[stack.top]) >= precedence(ch)) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, ch);
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (stack.top != -1 && stack.data[stack.top] != '(') {
                postfix[j++] = pop(&stack);
            }
            if (stack.top == -1) {
                printf("Error: Mismatched parentheses\n");
                exit(EXIT_FAILURE);
            }
            pop(&stack);  // Discard '('
        }
        i++;
    }

    while (stack.top != -1) {
        if (stack.data[stack.top] == '(') {
            printf("Error: Mismatched parentheses\n");
            exit(EXIT_FAILURE);
        }
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
}

void generateTAC(char *postfix) {
    Stack stack;
    stack.top = -1;
    int t = 1;
    char result[3] = "t1";
    char operand1[2], operand2[2];
    int i = 0;

    printf("Three Address Code:\n");

    while (postfix[i] != '\0') {
        char ch = postfix[i];
        if (isdigit(ch)) {
            sprintf(operand1, " %c ", ch);
            push(&stack, result[0]);
            printf("%c =%s\n", result[0], operand1);
            result[1]++;
            t++;
        } else if (isOperator(ch)) {
            operand2[0] = pop(&stack);
            operand2[1] = '\0';
            operand1[0] = pop(&stack);
            operand1[1] = '\0';
            printf("%c = %s %c %s\n", result[0], operand1, ch, operand2);
            push(&stack, result[0]);
            result[1]++;
            t++;
        }
        i++;
    }
}

int main() {
    char infix[MAX_EXPR_SIZE], postfix[MAX_EXPR_SIZE];

    printf("Enter an infix arithmetic expression : ");
    fgets(infix, MAX_EXPR_SIZE, stdin);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    generateTAC(postfix);

    return 0;
}
