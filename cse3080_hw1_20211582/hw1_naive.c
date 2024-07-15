#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STR 10000000
#define MAX_PAT 3000

char str[MAX_STR];
char pat[MAX_PAT];
int size_str = 0;
int size_pat = 0;
int main(void) {
	FILE* fp_str = fopen("string.txt", "r");
	FILE* fp_pat = fopen("pattern.txt", "r");
	FILE* fp_res = fopen("result_naive.txt", "w");
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
	size_str = strlen(str);
	size_pat = strlen(pat);
	if (size_str == 0) {
		printf("nothing in string.txt");
		return 0;
	}
	if (size_pat == 0) {
		printf("noting in pattern.txt");
		return 0;
	}
	int number = 0;
	int j = 0;
	int* answer = (int*)malloc(sizeof(int));
	for (int i = 0; i <= size_str - size_pat; i++) {
		for (j = i; j < i + size_pat; j++) {
			if (str[j] != pat[j - i]) break;
		}
		if (j == i + size_pat) {
			answer[number] = i;
			number++;
			answer = (int*)realloc(answer, (number + 1) * sizeof(int));
		}
	}
	fprintf(fp_res, "%d\n", number);
	for (int x = 0; x < number; x++) {
		fprintf(fp_res, "%d ", answer[x]);
	}
	fprintf(fp_res, "\n");
	fclose(fp_str);
	fclose(fp_pat);
	fclose(fp_res);
	free(answer);
	return 0;
}
