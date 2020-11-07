// https://www.geeksforgeeks.org/climits-limits-h-cc/

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned long long u64;

/* -------------------------------------------------- *
    Dynamic list
 * -------------------------------------------------- */

typedef struct node {
	u64 data;
	struct node *next;
} *node;

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

/* -------------------------------------------------- *
    Main progam
 * -------------------------------------------------- */

int main(int argc, char *argv[]) {
	assert(CHAR_BIT >= 8);
	assert(ULLONG_MAX >= 0xffffffffffffffff);

	if (argc < 2) {
		fprintf(stderr, "Range not specified.\n");
		return -1;
	}
	u64 range = strtoull(argv[1], NULL, 10);

	node prime_head = node_new(NULL, 2);
	node prime_last = node_new(prime_head, 3);

	u64 z = 0;
	for (u64 i = 6; i <= range; i += 6) {
		fprintf(stderr, "\r%llu out of %llu", i, range);
		double r = sqrt(i+1);
		int x[2] = {1, 1};
		for (node j = prime_head; j; j = j->next) {
			if (x[0]) x[0] = (i-1) % j->data;
			if (x[1]) x[1] = (i+1) % j->data;
			z += 1;
			if (!x[0] && !x[1]) break;
			if (j->data > r) break;
		}
		if (x[0]) prime_last = node_new(prime_last, i-1);
		if (x[1]) prime_last = node_new(prime_last, i+1);
	}
	fprintf(stderr, "\r");

	u64 total = 0;
	printf("[");
	for (node i = prime_head; i; i = i->next) {
		total += 1;
		printf("%llu%s", i->data, (i->next) ? ", " : "");
	}
	printf("]\n");
	printf("Total number of primes: %llu\n", total);
	printf("Range: %llu\n", range);
	printf("Total number of iterations: %llu\n", z);

	node_free(prime_head);
	return 0;
}
