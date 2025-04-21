#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX][3];
int top = -1;

void push(char *c) {
	strcpy(stack[++top], c);
}



void pop() {
	top--;
}

void displayStack() { int i;
	for ( i = 0; i <= top; i++) {
		printf("%s", stack[i]);
	}
}

int checkReduction() {
	if (top >= 2 && strcmp(stack[top], "S") == 0 && strcmp(stack[top - 1], "+") == 0 &&
	        strcmp(stack[top - 2], "S") == 0) {
		pop();
		pop(); // Remove + and last S
		strcpy(stack[top], "S");
		return 1; // Reduce S -> S + S
	}
	if (top >= 0 && strcmp(stack[top], "id") == 0) {
		strcpy(stack[top], "S"); // Reduce S -> id
		return 1;


	}
	return 0;
}

void shiftReduceParser(char input[]) {
	printf("%-15s %-15s %-15s\n", "Stack", "Input Buffer", "Parsing Action");
	printf("-------------------------------------------------------------\n");

	push("$");
	printf("%-15s %-15s %-15s\n", "$", input, "Shift");

	int i = 0;
	while (input[i] != '$') {
		if (input[i] == 'i' && input[i + 1] == 'd') {
			push("id");
			i += 2;
		} else {
			char temp[2] = {input[i++], '\0'};
			push(temp);
		}

		displayStack();
		printf("%-15s %-15s %-15s\n", "", &input[i], "Shift");

		while (checkReduction()) {
			displayStack();
			printf("%-15s %-15s %-15s\n", "", &input[i], "Reduce");
		}
	}

	while (checkReduction()) {
		displayStack();
		printf("%-15s %-15s %-15s\n", "", "$", "Reduce");
	}

	if (top == 1 && strcmp(stack[1], "S") == 0) {
		displayStack();
		printf("%-15s %-15s %-15s\n", "", "$", "Accept");
	} else {
		displayStack();
		printf("%-15s %-15s %-15s\n", "", "$", "Reject");


	}
}

int main() {
	char input[] = "id+id+id$"; // Input string to be parsed
	shiftReduceParser(input);
	return 0;
}
