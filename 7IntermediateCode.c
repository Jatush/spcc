#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX][10];


int top = -1;
int tempCount = 1;

// Push to stack
void push(char* str) {
	strcpy(stack[++top], str);
}

// Pop from stack
char* pop() {
	if (top == -1) return "";
	return stack[top--];
}

// Check if character is operator
int isOperator(char ch) {
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Return precedence of operators
int precedence(char op) {
	if (op == '*' || op == '/') return 2;
	if (op == '+' || op == '-') return 1;
	return 0;
}



// Convert infix to postfix
void infixToPostfix(char infix[], char postfix[]) {
	char opStack[MAX];
	int topOp = -1, i = 0, j = 0;
	char ch;

	while ((ch = infix[i++]) != '\0') {
		if (isspace(ch)) continue;

		if (isalnum(ch)) {
			postfix[j++] = ch;
		} else if (ch == '(') {
			opStack[++topOp] = ch;
		} else if (ch == ')') {
			while (topOp != -1 && opStack[topOp] != '(')
				postfix[j++] = opStack[topOp--];
			topOp--; // pop '('
		} else if (isOperator(ch)) {
			while (topOp != -1 && precedence(opStack[topOp]) >= precedence(ch))
				postfix[j++] = opStack[topOp--];
			opStack[++topOp] = ch;
		}
	}
	while (topOp != -1)
		postfix[j++] = opStack[topOp--];
	postfix[j] = '\0';

}

// Generate Three Address Code from postfix expression
void generateTAC(char postfix[], char resultVar) {
	int i = 0;
	char ch;
	char op1[10], op2[10], res[10];

	while ((ch = postfix[i++]) != '\0') {
		if (isalnum(ch)) {
			char str[2];
			str[0] = ch;
			str[1] = '\0';
			push(str);
		} else if (isOperator(ch)) {
			strcpy(op2, pop());
			strcpy(op1, pop());

			sprintf(res, "t%d", tempCount++);
			printf("%s = %s %c %s\n", res, op1, ch, op2);
			push(res);
		}
	}

// Final result assignment
	printf("%c = %s\n", resultVar, pop());


}

int main() {
	char input[MAX], expr[MAX], postfix[MAX];
	char resultVar;

	printf("Enter an arithmetic expression (e.g., a = b + c * d): ");
	fgets(input, MAX, stdin);

// Remove newline character
	input[strcspn(input, "\n")] = 0;

// Extract LHS (result variable) and RHS expression
	int i = 0, j = 0;
	while (input[i] != '=' && input[i] != '\0') {
		if (!isspace(input[i])) {
			resultVar = input[i];
		}
		i++;
	}

	i++; // Skip '='
	while (input[i] != '\0') {
		if (!isspace(input[i])) {
			expr[j++] = input[i];
		}


		i++;
	}
	expr[j] = '\0';

	infixToPostfix(expr, postfix);

	printf("\nPostfix Expression: %s\n", postfix);
	printf("Three Address Code:\n");
	generateTAC(postfix, resultVar);

	return 0;
}