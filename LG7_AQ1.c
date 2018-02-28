#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200

int findFirst(char *sent, char *sub) {
	int sentlen = strlen(sent);
	int sublen = strlen(sub);

	for (int i = 0; i <= sentlen - sublen; i++) {
		if (strncmp(sent + i, sub, sublen) == 0 && (i == 0 || sent[i - 1] == ' ') && (i == (sentlen - sublen) || sent[i + sublen] == ' '))
			return i;
	}
	return -1;
}

void replaceFirstOccurWord(char *sent, char *sub, int pos) {
	char after[MAX] = "";
	char before[MAX] = "";

	strncpy(before, sent, pos);
	strcpy(after, sent + pos + strlen(sub));

	strcpy(sent, before);
	strcat(sent, "* ");
	strcat(sent, after);
}

int main(void) {
	int pos;
	char text[MAX * 2];
	char str[10];
	printf("Enter a text: ");
	scanf("%[^\n]", text);
	printf("Enter a string: ");
	scanf("%s", str);

	printf("Old text: %s\n", text);
	pos = findFirst(text, str);
	replaceFirstOccurWord(text, str, pos);
	printf("New Text: %s\n", text);

	return 0;

}