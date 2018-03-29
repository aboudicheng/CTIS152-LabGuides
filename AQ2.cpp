#include <stdio.h>
#include <math.h>

int recursive(int num, int pow) {
	if (num == 0) {
		return 0;
	}
	else {
		if (num % 10 == 1) {
			return powf(2, pow) + recursive(num / 10, pow + 1);
		}
		else {
			return recursive(num / 10, pow + 1);
		}
	}
}

int main(void) {
	int num;
	printf("Enter a binary number: ");
	scanf("%d", &num);
	printf("The Decimal is %d\n", recursive(num, 0));



	return 0;
}