#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ELEMENTS 1000002

typedef struct {
	int key;
} element;
element max_heap[MAX_ELEMENTS];
element min_heap[MAX_ELEMENTS];
element copy_max[MAX_ELEMENTS];
element copy_min[MAX_ELEMENTS];
int n = 0;
int m = 0;

void insert_max_heap(element item, int* n);
void insert_min_heap(element item, int* m);
element delete_max_heap(int* n);
element delete_min_heap(int* m);

int main(int argc, char** argv) {
	double start, end;
	start = (double)clock() / CLOCKS_PER_SEC;
	if (argc != 2) {
		printf("usage: ./hw2 input_filename\n");
		return 0;
	}
	FILE* fp = fopen(argv[1], "r");
	if (!fp) {
		printf("The input file does not exist.\n");
		return 0;
	}
	FILE* check = fopen("hw2_result.txt", "w");
	fclose(check);
	char line[15];
	while (!feof(fp)){
		char command[8];
		int num = 0;
		fgets(line, 15, fp);
		sscanf(line, "%s %d", command, &num);
		if (strncmp(command, "INSERT", 6) == 0) {
			element item;
			item.key = num;
			insert_max_heap(item, &n);
			insert_min_heap(item, &m);
		}
		else if (strncmp(command, "ASCEND", 6) == 0) {
			memcpy(copy_min, min_heap, sizeof(min_heap));
			FILE* fw = fopen("hw2_result.txt", "a");
			int a;
			a = m;
			while (a > 0) {
				element data;
				data = delete_min_heap(&a);
				fprintf(fw, "%d ", data.key);
			}
			fprintf(fw, "\n");
			fclose(fw);
		}
		else if (strncmp(command, "DESCEND", 7) == 0) {
			memcpy(copy_max, max_heap, sizeof(max_heap));
			FILE* fw = fopen("hw2_result.txt", "a");
			int b;
			b = n;
			while (b > 0) {
				element data;
				data = delete_max_heap(&b);
				fprintf(fw, "%d ", data.key);
			}
			fprintf(fw, "\n");
			fclose(fw);
		}
	}
	printf("output written to hw2_result.txt.\n");
	fclose(fp);
	end = (((double)clock()) / CLOCKS_PER_SEC);
	printf("running time: %f seconds\n", (end-start));
	return 0;
}

void insert_max_heap(element item, int* n) {
	/* insert item into a max heap of current size *n */
	int i;
	if (*n == MAX_ELEMENTS - 1) {
		exit(1);
	}
	i = ++(*n);
	while ((i != 1) && (item.key > max_heap[i / 2].key)) {
		max_heap[i] = max_heap[i / 2];
		i /= 2;
	}
	max_heap[i] = item;
}

void insert_min_heap(element item, int* m) {
	int i;
	if (*m == MAX_ELEMENTS - 1) {
		exit(1);
	}
	i = ++(*m);
	while ((i != 1) && (item.key < min_heap[i / 2].key)) {
		min_heap[i] = min_heap[i / 2];
		i /= 2;
	}
	min_heap[i] = item;
}

element delete_max_heap(int* n) {
	/* delete element with the highest key from the heap */
	int parent, child;
	element item, temp;
	if (*n == 0) {
		exit(1);
	}
	/* save value of the element with the largest key */
	item = copy_max[1];
	/* use the last element in the heap to adjust heap */
	temp = copy_max[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		/* find the larger child of the current parent */
		if ((child < *n) && (copy_max[child].key < copy_max[child + 1].key)) child++;
		if (temp.key >= copy_max[child].key) break;
		/* move to the next lower level */
		copy_max[parent] = copy_max[child];
		parent = child;
		child *= 2;
	}
	copy_max[parent] = temp;
	return item;
}

element delete_min_heap(int* m) {
	int parent, child;
	element item, temp;
	if (*m == 0) {
		exit(1);
	}
	/* save value of the element with the largest key */
	item = copy_min[1];
	/* use the last element in the heap to adjust heap */
	temp = copy_min[(*m)--];
	parent = 1;
	child = 2;
	while (child <= *m) {
		/* find the larger child of the current parent */
		if ((child < *m) && (copy_min[child].key > copy_min[child + 1].key)) child++;
		if (temp.key <= copy_min[child].key) break;
		/* move to the next lower level */
		copy_min[parent] = copy_min[child];
		parent = child;
		child *= 2;
	}
	copy_min[parent] = temp;
	return item;
}