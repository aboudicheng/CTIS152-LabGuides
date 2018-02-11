#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define HARVEST 3

void read(FILE *ptr, int **farmer, int *size) {
	*size = 0;
	int j = 0;
	int dummy;
	while (fscanf(ptr, "%d", &dummy) != EOF) {
		j = 0;
		*(*(farmer + *size) + j) = dummy;
		for (int i = 1; i < HARVEST; i++) {
			fscanf(ptr, "%d", *(farmer + *size) + i);
		}
		*size += 1;
	}
}

void calculate(int **farmer, int farmerno) {
	int maxQuota, totalWeight = 0;
	double support, payment;
	for (int i = 0; i < HARVEST; i++) {
		if (*(*(farmer + farmerno - 1) + i) > 375) {
			maxQuota = *(*(farmer + farmerno - 1) + i);
			printf("\nYour tea weight is %d kg\n", *(*(farmer + farmerno - 1) + i));
			printf("Sorry! The maximum QUOTA for each harvesting is: 375\n");
			*(*(farmer + farmerno - 1) + i) = 375;
		}
		totalWeight += *(*(farmer + farmerno - 1) + i);
	}
	payment = (double)totalWeight * 0.9;
	support = payment * 0.2;

	printf("\nYour total tea weight: %d kg\n", totalWeight);
	printf("The Support from WorldBank is: %.2f TL\n", support);
	printf("The Payment from RHS Tea Company is : %.2f TL\n", payment);

}

int main(void) {
	FILE *ptr = fopen("tea.txt", "r");
	if (ptr == NULL)
		printf("Cannot open file.\n");
	else {
		int **farmer = (int **)malloc(MAX * sizeof(int *));
		for (int i = 0; i < MAX; i++) {
			farmer[i] = (int *)malloc(HARVEST * sizeof(int));
		}
		int size, farmerno;
		read(ptr, farmer, &size);

		printf("There are %d farmers\n", size);
		do {
			printf("Please enter the farmer no: ");
			scanf("%d", &farmerno);
		} while (!(farmerno >= 1 && farmerno <= 10));
		calculate(farmer, farmerno);

		fclose(ptr);
		free(farmer);
	}
	
	return 0;
}
