#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int car_id;
	char model[20];
	int year;
	int hp;
}car_t;

typedef struct {
	int driverId;
	char name[20];
	int age;
	int car_id;
}driver_t;

void printCars(car_t c[]) {
	printf("--- Cars ---\n");
	for (int i = 0; i < 4; i++) {
		printf("%d %s %d %d\n", c[i].car_id, c[i].model, c[i].year, c[i].hp);
	}
}

int getCar(car_t c[], int id) {
	for (int i = 0; i < 4; i++) {
		if (c[i].car_id == id)
			return i;
	}
	return -1;
}

void printDriversAndCars(driver_t d[], car_t c[]) {
	int getc;
	printf("--- Drivers and their cars ---\n");
	for (int i = 0; i < 7; i++) {
		printf("%d %s %d %d ", d[i].driverId, d[i].name, d[i].age, d[i].car_id);
		getc = getCar(c, d[i].car_id);
		if (getc != -1)
			printf("%s %d %d\n", c[getc].model, c[getc].year, c[getc].hp);
		else
			printf("UNKOWN\n");
	}
}

void printSameDrivers(driver_t d[], car_t c[]) {
	int count;
	for (int i = 0; i < 4; i++) {
		count = 0;
		printf("--- %s ---\n", c[i].model);
		for (int j = 0; j < 7; j++) {
			if (d[j].car_id == c[i].car_id) {
				printf("%d %s\n", d[j].driverId, d[j].name);
				count++;
			}
		}
		printf("There are %d driver(s)\n", count);
	}
}

int main(void) {
	car_t cars[] = {
		{ 128, "Nissan", 2011, 120 },
		{ 23, "Mazda", 2012, 125 },
		{ 32, "Toyota", 2000, 110 },
		{ 25, "Renault", 2005, 123 }
	};

	driver_t drivers[] = {
		{ 5934, "John", 24, 32 },
		{ 7142, "Marc", 29, 128 },
		{ 1111, "Hans", 23, 25 },
		{ 2343, "Tom", 21, 23 },
		{ 3425, "Jill", 20, 128 },
		{ 5465, "Jim", 27, 23 },
		{ 5999, "Tim", 30, 120 }
	};
	int choice;
	for (int i = 0; i < 30; i++)
		printf("=");
	printf("\n1. Print all cars.\n2. Print all drivers and their cars.\n3. Print the drivers using the same car.\n4. Exit\n");
	printf("Choice: ");
	scanf("%d", &choice);
	while (choice != 4) {

		for (int i = 0; i < 30; i++)
			printf("=");
		printf("\n");
		if (choice == 1)
			printCars(cars);
		else if (choice == 2)
			printDriversAndCars(drivers, cars);
		else if (choice == 3)
			printSameDrivers(drivers, cars);
		for (int i = 0; i < 30; i++)
			printf("=");
		printf("\n1. Print all cars.\n2. Print all drivers and their cars.\n3. Print the drivers using the same car.\n4. Exit\n");
		printf("Choice: ");
		scanf("%d", &choice);

	}
	return 0;
}