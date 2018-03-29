#include <stdio.h>
#include <string.h>
#include "stack_int.h"

int postfix(char *string) {
	stack_t s;
	initialize_s(&s);

	int i = 0, len = strlen(string), num, res, a, b;
	while (i < len) {
		if (string[i] >= '0' && string[i] <= '9') {
			num = string[i] - '0';
			push(&s, num);
		}
		else if (string[i] == '+') {
			b = pop(&s);
			a = pop(&s);
			res = a + b;
			push(&s, res);
		}

		else if (string[i] == '-') {
			b = pop(&s);
			a = pop(&s);
			res = a - b;
			push(&s, res);
		}

		else if (string[i] == '*') {
			b = pop(&s);
			a = pop(&s);
			res = a * b;
			push(&s, res);
		}

		else if (string[i] == '/') {
			b = pop(&s);
			a = pop(&s);
			res = a / b;
			push(&s, res);
		}
		i++;
	}

	return res;
}

int main(void) {
	char exp[20];
	printf("Enter an expression: ");
	scanf("%[^\n]", exp);
	printf("The result is %d\n", postfix(exp));

	return 0;
}