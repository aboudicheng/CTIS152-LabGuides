#include <stdio.h>
#include <stdlib.h>
#define UNISIZE 3
#define UNISTU 8

typedef struct {
	int id;
	char name[20];
	int age, year;
	double fee;
}attendees_t;

typedef struct {
	int id;
	char name[20],
		martial[20];
	attendees_t a[8];
}university_t;

void readFile(FILE *ptr, university_t p[]) {
	for (int i = 0; i < UNISIZE; i++) {
		fscanf(ptr, "%d %s %s", &p[i].id, &p[i].name, &p[i].martial);
		for (int j = 0; j < UNISTU; j++) {
			fscanf(ptr, "%d %s %d %d", &p[i].a[j].id, &p[i].a[j].name, &p[i].a[j].age, &p[i].a[j].year);
		}
	}
}

void calcFee(university_t p[]) {
	for (int i = 0; i < UNISIZE; i++) {
		for (int j = 0; j < UNISTU; j++) {
			if (p[i].a[j].year <= 3)
				p[i].a[j].fee = p[i].a[j].year * 100;
			else if (p[i].a[j].year <= 10)
				p[i].a[j].fee = p[i].a[j].year * 125;
			else
				p[i].a[j].fee = p[i].a[j].year * ( 125 + (p[i].a[j].year - 10) * 25);
		}
	}
}

void display(university_t p[]) {
	for (int i = 0; i < UNISIZE; i++) {
		printf("%s\nMartial Art: %s\n", p[i].name, p[i].martial);
		printf("ID     NAME      AGE   Years Trained    Fee\n*** ***********  ***   ************   ********\n");
		for (int j = 0; j < UNISTU; j++) {
			printf("%d %s\t %d\t   %d\t      %.2fTL\n", p[i].a[j].id, p[i].a[j].name, p[i].a[j].age, p[i].a[j].year, p[i].a[j].fee);
		}
	}
}

int main(void) {
	FILE *ptr = fopen("mArtsDay.txt", "r");
	if (ptr == NULL)
		printf("Cannot open file.\n");
	else {
		university_t p[UNISIZE];
		readFile(ptr, p);
		calcFee(p);
		display(p);
	}
	return 0;
}
