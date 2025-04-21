#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char *keywords[] = {"int", "float", "char", "double", "return", "if", "else", "while",
                          "for", "do", "break", "continue", "switch", "case", "default", "void", "str"
                         };
const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

int isKeyword(const char *word) {
	int i;
	for ( i = 0; i < num_keywords; i++) {
		if (strcmp(word, keywords[i]) == 0) return 1;
	}
	return 0;
}

int isOperator(char ch) {
	int i;
	char operators[] = "+-*/%=<>&|!";
	for ( i = 0; i < strlen(operators); i++) {
		if (ch == operators[i]) return 1;

	}
	return 0;
}

int isPunctuation(char ch) {
	int i;
	char punctuations[] = "();{},:[]";
	for ( i = 0; i < strlen(punctuations); i++) {
		if (ch == punctuations[i]) return 1;
	}
	return 0;
}

typedef struct {
	char token[50];
	int count;
} Token;

Token keywords_list[50], identifiers_list[50], constants_list[50], operators_list[50],
      punctuations_list[50], strings_list[50];
int keyword_count = 0, identifier_count = 0, constant_count = 0, operator_count = 0,
    punctuation_count = 0, string_count = 0;

void addToken(Token list[], int *count, const char *token) {
	int i;
	for ( i = 0; i < *count; i++) {
		if (strcmp(list[i].token, token) == 0) {
			list[i].count++;
			return;

		}
	}
	strcpy(list[*count].token, token);
	list[*count].count = 1;
	(*count)++;
}

void lexicalAnalyzer(const char *code) {
	int i = 0;
	while (code[i] != '\0') {
		if (isspace(code[i])) {
			i++;
			continue;
		}

// Identifier or Keyword
		if (isalpha(code[i]) || code[i] == '_') {
			char buffer[50];
			int j = 0;
			while (isalnum(code[i]) || code[i] == '_') {
				buffer[j++] = code[i++];
			}
			buffer[j] = '\0';
			if (isKeyword(buffer)) addToken(keywords_list, &keyword_count, buffer);
			else addToken(identifiers_list, &identifier_count, buffer);
		}

// Numeric constant
		else if (isdigit(code[i])) {
			char buffer[50];
			int j = 0;
			while (isdigit(code[i]) || code[i] == '.') {
				buffer[j++] = code[i++];
			}
			buffer[j] = '\0';
			addToken(constants_list, &constant_count, buffer);
		}

// String literal
		else if (code[i] == '"') {
			char buffer[50];
			int j = 0;
			buffer[j++] = code[i++]; // opening quote
			while (code[i] != '"' && code[i] != '\0') {
				buffer[j++] = code[i++];
			}
			if (code[i] == '"') buffer[j++] = code[i++];
			buffer[j] = '\0';
			addToken(strings_list, &string_count, buffer);
		}

// Operators (basic 1-char only for simplicity, extendable)

		else if (isOperator(code[i])) {
			char buffer[3] = {code[i], '\0'};
			if ((code[i] == '=' || code[i] == '<' || code[i] == '>' || code[i] == '!') && code[i + 1] ==
			        '=') {
				buffer[1] = code[i + 1];
				buffer[2] = '\0';
				i += 2;
			} else {
				i++;
			}
			addToken(operators_list, &operator_count, buffer);
		}

// Punctuation
		else if (isPunctuation(code[i])) {
			char buffer[2] = {code[i], '\0'};
			addToken(punctuations_list, &punctuation_count, buffer);
			i++;
		}

// Unknown character
		else {
			i++;
		}
	}

// Output

	printf("\n--- Lexical Analysis Result ---\n");
	printf("Keywords: ");
	for ( i = 0; i < keyword_count; i++) {
		printf("%s ", keywords_list[i].token);
	}
	printf("\nIdentifiers: ");
	for ( i = 0; i < identifier_count; i++) {
		printf("%s ", identifiers_list[i].token);
	}
	printf("\nConstants: ");
	for ( i = 0; i < constant_count; i++) {
		printf("%s ", constants_list[i].token);
	}
	printf("\nOperators: ");
	for ( i = 0; i < operator_count; i++) {
		printf("%s ", operators_list[i].token);
	}
	printf("\nPunctuations: ");
	for ( i = 0; i < punctuation_count; i++) {
		printf("%s ", punctuations_list[i].token);
	}
	printf("\nStrings: ");
	for ( i = 0; i < string_count; i++) {
		printf("%s ", strings_list[i].token);
	}
	printf("\n");


}

int main() {
	const char code[] = "int main() { int a, b; a = 10; char str[] = \"hello\"; return 0; }";
	printf("Input Code: %s\n", code);
	lexicalAnalyzer(code);
	return 0;
}
