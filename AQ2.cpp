#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int id;
	char name[30];
	double price;
}books_t;

void menu(int *choice) {
	printf("1. Display the current library\n2. Add new book to the library\n3. Exit\n");
	printf("Enter you choice: ");
	scanf("%d", choice);
	while (*choice < 1 || *choice > 3) {
		printf("Re-Enter you choice: ");
		scanf("%d", choice);
	}
}

void readFile(FILE *ptr, books_t b[], int *n) {
	int size = 0;
	while (fscanf(ptr, "%d %s %lf", &b[size].id, &b[size].name, &b[size].price) != EOF) {
		size++;
	}
	*n = size;
}

int newRecord(books_t b[], int *n) {
	if (*n > 6)
		return 0;
	printf("Please enter new book info\n");
	printf("Enter Book ID:");
	scanf("%d", &b[*n].id);
	printf("Enter Book Name: ");
	scanf("%s", &b[*n].name);
	printf("Enter Book Price: ");
	scanf("%lf", &b[*n].price);
	*n += 1;
	return 1;
}

void display(books_t b[], int n) {
	for (int i = 0; i < n; i++) {
		printf("\nID: %d\nName: %s\nPrice: %.2f\n", b[i].id, b[i].name, b[i].price);
	}
}

int main(void) {
	FILE *ptr = fopen("AQ2.txt", "r");
	if (ptr == NULL)
		printf("Cannot open file.\n");
	else {
		int choice, size;
		books_t b[7];
		menu(&choice);
		readFile(ptr, b, &size);
		while (choice != 3) {
			
			if (choice == 1)
				display(b, size);
			else if (choice == 2)
				newRecord(b, &size);
			menu(&choice);
		}
		printf("Goodbye.\n");
	}
	return 0;
}