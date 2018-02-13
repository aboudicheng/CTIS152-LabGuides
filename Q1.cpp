#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char info[20];
	double price;
	int discount;
} produc_t;

void readFromFile(FILE *ptr, produc_t *d, int n) {
	int dummy;
	fscanf(ptr, "%d", &dummy);
	for (int i = 0; i < n; i++) {
		fscanf(ptr, "%s", &(d[i].info));
		fscanf(ptr, "%lf %d", &(d[i].price), & (d[i].discount));
	}
}

void displayAllProducts(produc_t *d, int n) {
	printf("There are %d products in the market\n\n", n);
	printf("PRODUCT NAME\tPRICE\t   DISCOUNT\tDISC. PRICE\tSAVED AMOUNT\n************\t*********   *********\t************\t************\n");
	for (int i = 0; i < n; i++) {
		printf("%-13s     %6.2f $      %%%d\t   %5.2f $\t   %5.2f $\n", d[i].info, d[i].price, d[i].discount, d[i].price - d[i].price * d[i].discount * 0.01, d[i].price * d[i].discount * 0.01);
	}
}

int main(void) {
	FILE *ptr = fopen("amazon.txt", "r");
	if (ptr == NULL)
		printf("Cannot open file.\n");
	else {
		int products;
		produc_t *p;
		fscanf(ptr, "%d", &products);
		p = (produc_t *)malloc(sizeof(produc_t) * products);
		readFromFile(ptr, p, products);
		displayAllProducts(p, products);
		fclose(ptr);
		free(p);
	}
	return 0;
}

