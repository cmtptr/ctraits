#include <stdio.h>
#include <stdlib.h>

#include "cat.h"
#include "num.h"

static int compar(const void *a, const void *b)
{
	const struct cat *c = *(struct cat **)a;
	return c->ord.impl->cmp(&c->ord, &(*(struct cat **)b)->ord);
}

int main()
{
	struct cat *cats[] = {
		cat_new("Tom", 5),
		cat_new("Pookie", 3),
		cat_new("Jack Bauer", 36),
		cat_new("Fluffy", 14),
	};
	puts("==== before ====");
	for (size_t i = 0; i < sizeof cats / sizeof *cats; ++i) {
		struct num *n = num_new(i);
		fmt_print("[{}] {}\n", &n->fmt, &cats[i]->fmt);
		num_free(n);
	}
	qsort(cats, sizeof cats / sizeof *cats, sizeof *cats, compar);
	puts("==== after  ====");
	for (size_t i = 0; i < sizeof cats / sizeof *cats; ++i) {
		struct num *n = num_new(i);
		fmt_print("[{}] {}\n", &n->fmt, &cats[i]->fmt);
		num_free(n);
		cat_free(cats[i]);
	}
	return 0;
}
