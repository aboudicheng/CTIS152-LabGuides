#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct {
	int day, month, year;
} date_t;

typedef struct {
	int tour;
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
	printf("Enter your choice: ");
	scanf("%d", &choice);
	while (choice < 1 || choice > 3) {
		printf("Choose again: ");
		scanf("%d", &choice);
	}

	return choice;
}

int readFromFile(FILE *ptr, tour_t *t) {
	int n = 0;
	while (fscanf(ptr, "tour-%d %[^:]:%d.%d.%d%d%lf%[^\n]\n", &t[n].tour, &t[n].dest, &t[n].date.day, &t[n].date.month, &t[n].date.year, &t[n].days, &t[n].price, &t[n].airline) != EOF) {
		n++;
	}

	return n;
}

void displayATour(tour_t *t, int i) {
	printf("tour-%-2d %-25s%d.%d.%d\t%-3d   %-7.2f   %-15s\n", t[i].tour, t[i].dest, t[i].date.day, t[i].date.month, t[i].date.year, t[i].days, t[i].price, t[i].airline);
}

void displayAllTour(tour_t *t, int n) {
	printf("Tour Code  Tour Name\t\tDate\t   #ofDays  Price (Euro)   AIRLINE\n");
	printf("********************************************************************************\n");
	for (int i = 0; i < n; i++) {
		displayATour(t, i);
	}
}

void swap(tour_t *x, tour_t *y) {
	tour_t temp = *x;
	*x = *y;
	*y = temp;
}

void bubbleSort(tour_t *t, int n) {
	int sort, pass = 1;
	int i;
	do {
		sort = 1;
		for (i = 0; i < n - pass; i++) {
			if (strcmp(t[i].dest, t[i + 1].dest) > 0) {
				swap(&t[i], &t[i + 1]);
				sort = 0;
			}
		}
		pass++;
	} while (!sort);
}

int searchByMonth(tour_t *t, int month, int n) {

	int count = 0;
	int i;

	for (i = 0; i < n; i++) {
		if (t[i].date.month == month) {
			displayATour(t, i);
			count++;
		}
	}

	return count;
}

int searchByDestination(tour_t *t, char *str, int n) {
	int i, j, count = 0;
	int len = strlen(str);

	for (i = 0; i < n; i++) {
		for (j = 0; j <= strlen(t[i].dest); j++) {
			if (strncmp(t[i].dest + j, str, len) == 0) {
				displayATour(t, i);
				count++;
			}
		}
	}
	return count;
}

int searchByCode(tour_t *t, int code, int n) {
	int top = 1, bottom = n, middle;

	while (top <= bottom) {
		middle = (top + bottom) / 2;
		if (t[middle].tour == code) {
			displayATour(t, middle);
			return middle;
		}
		else if (t[middle].tour > code)
			bottom = middle - 1;
		else
			top = middle + 1;
	}
	return -1;
}

int main(void) {
	FILE *ptr = fopen("tour.txt", "r");
	if (ptr == NULL)
		printf("Cannot open file.\n");
	else {
		int choice, tournum, code;
		char dest[100] = "";
		char res;
		tour_t t[MAX];
		tournum = readFromFile(ptr, t);
		bubbleSort(t, tournum);
		displayAllTour(t, tournum);
		choice = menu();
		while (choice != 3) {
			//if choice is 1
			if (choice == 1) {
				printf("Enter the destination: ");
				scanf("%s", dest);

				int count = searchByDestination(t, dest, tournum);
				if (count != 0) {
					printf("There are %d tour(s) with the specified criteria!\n", count);

					printf("Enter the tour program code to register: tour-");
					scanf("%d", &code);
					if (searchByCode(t, code, tournum) != -1) {
						printf("Early reservation (y/n)? ");
						scanf(" %c", &res);
						if (res == 'y') {
							printf("Please pay %.2f Euro\n", t[code + 1].price * 55 / 100);
						}
						else {
							printf("Please pay %.2f Euro\n", t[code + 1].price);
						}
					}
					else
						printf("You have entered a wrong tour code!!\n");
				}
				else
					printf("There is no tour with the specified criteria\n");
			}
			//if choice is 2
			else {
				int month, monthCount;

				//prompt
				printf("Enter the month to list the tours: ");
				scanf("%d", &month);

				//validate
				while (month > 12 || month < 1) {
					printf("Enter the month to list the tours: ");
					scanf("%d", &month);
				}

				monthCount = searchByMonth(t, month, tournum);

				if (monthCount != 0) {
					printf("There are %d tour(s) with the specified criteria!\n", monthCount);

					printf("Enter the tour program code to register: ");
					printf("tour-");
					scanf("%d", &code);

					if (searchByCode(t, code, tournum) != -1) {
						printf("Early reservation (y/n)? ");
						scanf(" %c", &res);
						if (res == 'y') {
							printf("Please pay %.2f Euro\n", t[code + 1].price * 55 / 100);
						}
						else {
							printf("Please pay %.2f Euro\n", t[code + 1].price);
						}
					}
					else
						printf("You have entered a wrong tour code!!\n");
				}
				else {
					printf("There is no tour with the specified criteria\n");
				}
			}

			choice = menu();
		}
	}

	return 0;
}
