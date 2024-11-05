# Data_Structure_Project
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '/': case '*': return 2;
        case '+': case '-': return 1;
        default: return -1;
    }
}

int shouldPop(char topOp, char currentOp) {
    int precTop = precedence(topOp);
    int precCurrent = precedence(currentOp);
    if (precTop > precCurrent)
        return 1;
    if (precTop == precCurrent && currentOp != '^')
        return 1;
    return 0;
}

void infixToPostfix(char* infix) {
    int len = strlen(infix);
    char postfix[len + 1];
    char stack[len];
    int postIdx = 0;
    int stackIdx = -1;

    for (int i = 0; i < len; i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[postIdx++] = ch;
        } else if (ch == '(') {
            stack[++stackIdx] = ch;
        } else if (ch == ')') {
            while (stackIdx != -1 && stack[stackIdx] != '(') {
                postfix[postIdx++] = stack[stackIdx--];
            }
            stackIdx--;
        } else {
            while (stackIdx != -1 && shouldPop(stack[stackIdx], ch)) {
                postfix[postIdx++] = stack[stackIdx--];
            }
            stack[++stackIdx] = ch;
        }
    }

    while (stackIdx != -1) {
        postfix[postIdx++] = stack[stackIdx--];
    }

    postfix[postIdx] = '\0';
    printf("Postfix: %s\n", postfix);
}

int main() {
    char infix[] = "a+b*(c^d-e)^(f+g*h)-i";
    infixToPostfix(infix);
    return 0;
}
