#include <stdio.h>
#include <stdlib.h>

typedef struct {
	double avg,
		avg_rebound;
} score_t;

typedef struct {
	char name[20];
	int age;
	double length;
	score_t score;
} playerinfo_t;

void readFromFile(FILE *ptr, playerinfo_t p[], int *n) {
	int size = 0;
	while (fscanf(ptr, "%s %d %lf %lf %lf", &p[size].name, &p[size].age, &p[size].length, &p[size].score.avg, &p[size].score.avg_rebound) != EOF) {
		size++;
	}
	*n = size;
}

void displayAll(playerinfo_t p[], int n) {
	printf("NAME\tAge   Length   Avg_Score   Avg_Rebound\n");
	for (int k = 0; k < 50; k++)
		printf("-");
	printf("\n");
	for (int i = 0; i < n; i++) {
		printf("%-8s %2d\t %4.2f\t %5.2f\t\t%5.2f\n", p[i].name, p[i].age, p[i].length, p[i].score.avg, p[i].score.avg_rebound);
	}
}

void findBestRebound(int n, playerinfo_t p[], double *max, int *index) {
	*max = p[0].score.avg_rebound;
	*index = 0;
	for (int i = 0; i < n; i++) {
		if (p[i].score.avg_rebound > *max) {
			*max = p[i].score.avg_rebound;
			*index = i;
		}
	}
}

void findAvgHeight(int n, playerinfo_t p[], double *length) {
	*length = 0;
	for (int i = 0; i < n; i++) {
		*length += p[i].length;
	}
	*length /= n;
}

int main(void) {
	FILE *ptr = fopen("players.txt", "r");
	if (ptr == NULL)
		printf("Cannot open file.\n");
	else {
		int size, index;
		double max, length;
		playerinfo_t *p = (playerinfo_t *)malloc(sizeof(playerinfo_t) * 20);
		readFromFile(ptr, p, &size);
		displayAll(p, size);
		findBestRebound(size, p, &max, &index);
		findAvgHeight(size, p, &length);

		printf("The Best rebound player: \n");
		printf("NAME\tAge   Length   Avg_Score   Avg_Rebound\n");
		for (int k = 0; k < 50; k++)
			printf("-");
		printf("\n");
		printf("%-8s %2d\t %4.2f\t %5.2f\t\t%5.2f\n", p[index].name, p[index].age, p[index].length, p[index].score.avg, p[index].score.avg_rebound);
		printf("The Avg Length of all players: %.2f\n", length);
		
		fclose(ptr);
		free(p);
	}
	return 0;
}