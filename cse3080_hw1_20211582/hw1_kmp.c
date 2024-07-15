#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STR 10000000
#define MAX_PAT 3000

char str[MAX_STR];
char pat[MAX_PAT];
int failure[MAX_PAT];
int size_str = 0;
int size_pat = 0;

void fail(char* pattern);

int main(void) {
	FILE* fp_str = fopen("string.txt", "r");
	FILE* fp_pat = fopen("pattern.txt", "r");
	FILE* fp_res = fopen("result_kmp.txt", "w");
	if (!fp_str) {
		printf("string file error!\n");
		return 0;
	}
	if (!fp_pat) {
		printf("pattern file error!\n");
		return 0;
	}
	fgets(str, MAX_STR, fp_str);
	fgets(pat, MAX_PAT, fp_pat);

	size_str = strlen(str)-1;
	size_pat = strlen(pat)-1;

	if (size_str == 0) {
		printf("nothing in string.txt");
		return 0;
	}
	if (size_pat == 0) {
		printf("noting in pattern.txt");
		return 0;
	}

	fail(pat);

	int i = 0, j = 0;
	int number = 0;
	int* answer = (int*)malloc(sizeof(int));
	while (i < size_str && j < size_pat) {
		if (str[i] == pat[j]) { i++; j++; }
		else  if (j == 0) i++;
		else j = failure[j - 1] + 1;
		if (j == size_pat) {
			answer[number] = i;
			number++;
			answer = (int*)realloc(answer, (number + 1) * sizeof(int));
		}
	}
	printf("%d\n", number);
	for (int x=0 ;x<number; x++) {
		printf("%d", answer[x]);
	}
	printf("\n");

	fprintf(fp_res, "%d\n", number);
	for (int x = 0; x < number; x++) {
		fprintf(fp_res, "%d", answer[x]);
	}

	fprintf(fp_res, "\n");
	fclose(fp_str);
	fclose(fp_pat);
	fclose(fp_res);
	free(answer);
	return 0;
}

void fail(char* patttern) {
	int i, n = strlen(pat);
	failure[0] = -1;
	for (int j = 1; j < n; j++) {
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0)) i = failure[i];
		if (pat[j] == pat[i + 1]) failure[j] = i + 1;
		else failure[j] = -1;
	}
}
