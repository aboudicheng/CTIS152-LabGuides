#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct {
	int day, month, year;
} date_t;

typedef struct {
	char tour[50] = "";
	char dest[50] = "";
	date_t date;
	int days;
	double price;
	char airline[50] = "";
} tour_t;

int menu() {
	int choice;
	printf("MENU\n**************************\n");
	printf("1. Search for a destination\n2. Search by month\n3. EXIT\n");
	scanf("%d", &choice);
	while (choice < 1 || choice > 3) {
		printf("Choose again: ");
		scanf("%d", &choice);
	}

	return choice;
}

int readFromFile(FILE *ptr, tour_t *t) {
	int n = 0;
	while (fscanf("%s%[^:]%d.%d.%d%d%d%s", &t[n].tour, &t[n].dest, &t[n].date.day, &t[n].date.month, &t[n].date.year, &t[n].days, &t[n].price, &t[n].airline) != EOF) {
		n++;
	}

	return n;
}