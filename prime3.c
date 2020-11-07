#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef unsigned long long u64;
typedef struct node {
	u64 data;
	struct node *next;
} *node;

node node_new(node, u64);
void node_free(node);

int main(int argc, char *argv[]) {
	assert(CHAR_BIT >= 8);
	assert(ULLONG_MAX >= 0xffffffffffffffff);

	if (argc < 2) goto ERROR;
	if (!strcmp(argv[1], "find")) { if (argc == 4) goto FIND; else goto ERROR; }
	if (!strcmp(argv[1], "read")) { if (argc == 4) goto READ; else goto ERROR; }
	if (!strcmp(argv[1], "trim")) { if (argc == 5) goto TRIM; else goto ERROR; }
	goto ERROR;

READ:
{
	FILE *fp = fopen(argv[2], "rb");
	u64 read;

	u64 total = 0;
	while (fread(&read, sizeof(u64), 1, fp) > 0) {
		if (total) printf("%s", argv[3]);
		total += 1;
		printf("%llu", read);
	}
	printf("\nTotal: %llu\n", total);

	fclose(fp);
}
goto END;

TRIM:
{
	if (!strcmp(argv[2], argv[4])) {
		fprintf(stderr, "Source cannot be the same as destination.\n");
		return -1;
	}

	FILE *fp1 = fopen(argv[2], "rb");
	FILE *fp2 = fopen(argv[4], "wb");
	u64 read;
	u64 range = strtoull(argv[3], NULL, 10);

	while (fread(&read, sizeof(u64), 1, fp1) > 0) {
		if (read > range) break;
			fwrite(&read, sizeof(u64), 1, fp2);
	}

	fclose(fp1);
	fclose(fp2);
}
goto END;

FIND:
{
	FILE *fp = fopen(argv[2], "a+b");
	u64 read;
	rewind(fp);

	u64 range = strtoull(argv[3], NULL, 10);
	node prime_head = node_new(NULL, 3);
	node prime_tail = prime_head;
	u64 start = 6;

	while (fread(&read, sizeof(u64), 1, fp) > 0)
		prime_tail = node_new(prime_tail, read);

	if (prime_tail->data > 3) {
		start = prime_tail->data-1;
		if (start % 6) start = prime_tail->data+1;
		if (start % 6) {
			fprintf(stderr, "Reading invalid prime.\n");
			return -1;
		}
		start += 6;
	}

	for (u64 i = start; i <= range; i += 6) {
		fprintf(stderr, "\r%llu out of %llu", i, range);
		double r = sqrt(i+1);
		int x[2] = {1, 1};
		for (node j = prime_head; j; j = j->next) {
			if (j->data > r) break;
			if (x[0]) x[0] = (i-1) % j->data;
			if (x[1]) x[1] = (i+1) % j->data;
			if (!x[0] && !x[1]) break;
		}
		if (x[0]) {
			prime_tail = node_new(prime_tail, i-1);
			fwrite(&prime_tail->data, sizeof(u64), 1, fp);
		}
		if (x[1]) {
			prime_tail = node_new(prime_tail, i+1);
			fwrite(&prime_tail->data, sizeof(u64), 1, fp);
		}
	}
	fprintf(stderr, "\r");

	node_free(prime_head);
	fclose(fp);
}
goto END;

END:
	return 0;

ERROR:
	fprintf(stderr, "Usage: find <file> <range>\n");
	fprintf(stderr, "       read <file> <delim>\n");
	fprintf(stderr, "       trim <file> <range> <file>\n");
	return -1;
}

node node_new(node m, u64 data) {
	node n = (node) malloc(sizeof(struct node));
	n->data = data;
	n->next = NULL;
	if (m) m->next = n;
	return n;
}

void node_free(node m) {
	while (m) {
		node n = m->next;
		free(m);
		m = n;
	}
}
