#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char name[13];
	int stock, arrive;
} phones_t;

int rbinary_search(FILE *ptr, char *brand, int top, int bottom, int *step) {
	int middle;
	if (top <= bottom) {
		(*step)++;
		middle = (top + bottom) / 2;
		phones_t temp;
		fseek(ptr, (middle - 1) * sizeof(phones_t), SEEK_SET);
		fread(&temp, sizeof(phones_t), 1, ptr);

		if (strcmp(temp.name, brand) == 0)
			return middle;
		else if (strcmp(temp.name, brand) > 0)
			return rbinary_search(ptr, brand, top, middle - 1, step);
		else
			return rbinary_search(ptr, brand, middle + 1, bottom, step);
	}
	else
		return -1;
}

int main(void) {
	FILE *ptr = fopen("phones.bin", "rb");
	if (ptr == NULL)
		printf("Cannot open file.\n");
	else {
		phones_t temp;
		fseek(ptr, 0, SEEK_END);
		int size = ftell(ptr) / sizeof(phones_t);
		rewind(ptr);

		int step = 0;
		char brand[13];
		printf("Enter a phone brand to search: ");
		scanf("%s", brand);

		int res = rbinary_search(ptr, brand, 0, size, &step);
		if (res != -1) {
			fseek(ptr, (res - 1) * sizeof(phones_t), SEEK_SET);
			fread(&temp, sizeof(phones_t), 1, ptr);

			printf("After %d step(s) %s found with %d stocks and %d stocks will arrive\n", step, temp.name, temp.stock, temp.arrive);
		}
		else
			printf("After %d step(s) %s could not be found!\n", step, brand);
	}
}