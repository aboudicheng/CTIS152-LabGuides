#include <stdio.h>
#include "stack_int.h"

int menu() {
	int choice;
	do {
		printf("1) Count Stack\n2) Remove Maximum Element\n3) Send Nth to End\n4) Exit\n");
		printf("\nEnter your choice: ");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 4);

	return choice;
}

void displayStack(stack_t s) {
	printf("STACK CONTENT\n");
	while (!is_empty_s(&s)) {
		printf("%d\n", pop(&s));
	}
}

int countStack(stack_t s) {
	int count = 0;
	while (!is_empty_s(&s)) {
		pop(&s);
		count++;
	}
	return count;
}

void remMaxStack(stack_t *s) {
	stack_t temp;
	initialize_s(&temp);
	int max = s->data[s->top], num = 0, newpop;
	while (!is_empty_s(s)) {
		newpop = pop(s);
		push(&temp, newpop);
		num--;
		if (newpop > max)
			max = newpop;
	}

	while (!is_empty_s(&temp)) {
		newpop = pop(&temp);
		if (newpop != max)
			push(s, newpop);
	}
}

void sendNthToEnd(stack_t *s, int n) {
	stack_t temp;
	initialize_s(&temp);
	int newpop, i, bottom;

	for (i = 1; i < n; i++) {
		newpop = pop(s);
		push(&temp, newpop);
	}
	bottom = pop(s);

	while (!is_empty_s(s)) {
		newpop = pop(s);
		push(&temp, newpop);
	}

	push(s, bottom);
	while (!is_empty_s(&temp)) {
		newpop = pop(&temp);
		push(s, newpop);
	}
	
	
}

int main(void) {
	int num, choice;
	stack_t s;
	initialize_s(&s);

	printf("Enter a number: ");
	scanf("%d", &num);
	while (num != -9) {
		push(&s, num);
		printf("Enter a number: ");
		scanf("%d", &num);
	}

	choice = menu();

	while (choice != 4) {
		switch (choice) {
		case 1:
			displayStack(s);
			printf("Number of elements in the stack: %d\n", countStack(s));
			break;
		case 2:
			remMaxStack(&s);
			displayStack(s);
			break;
		case 3:
			int n;
			printf("Enter N: ");
			scanf("%d", &n);
			sendNthToEnd(&s, n);
			displayStack(s);
		}
		choice = menu();
	}
}