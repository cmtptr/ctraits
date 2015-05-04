#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "add.h"
#include "mat.h"
#include "mul.h"

struct priv {
	double data[3][3];
	struct mat mat;
};

#define mattopriv(m) ((struct priv *)((char *)(m) - offsetof(struct priv, mat)))
#define addtopriv(a) mattopriv((char *)(a) - offsetof(struct mat, add))
#define multopriv(m) mattopriv((char *)(m) - offsetof(struct mat, mul))

static void mat_add_add(struct add *a1, struct add *a2)
{
	struct priv *p1 = addtopriv(a1), *p2 = addtopriv(a2);
	for (size_t i = 0; i < sizeof p1->data / sizeof *p1->data; ++i)
		for (size_t j = 0; j < sizeof *p1->data / sizeof **p1->data; ++j)
			p1->data[i][j] += p2->data[i][j];
}

static void mat_add_sub(struct add *a1, struct add *a2)
{
	struct priv *p1 = addtopriv(a1), *p2 = addtopriv(a2);
	for (size_t i = 0; i < sizeof p1->data / sizeof *p1->data; ++i)
		for (size_t j = 0; j < sizeof *p1->data / sizeof **p1->data; ++j)
			p1->data[i][j] -= p2->data[i][j];
}

static const struct add_impl mat_add = {
	.add = mat_add_add,
	.sub = mat_add_sub,
};

static void mat_mul_mul(struct mul *m, double d)
{
	struct priv *p = multopriv(m);
	for (size_t i = 0; i < sizeof p->data / sizeof *p->data; ++i)
		for (size_t j = 0; j < sizeof *p->data / sizeof **p->data; ++j)
			p->data[i][j] *= d;
}

static void mat_mul_div(struct mul *m, double d)
{
	struct priv *p = multopriv(m);
	for (size_t i = 0; i < sizeof p->data / sizeof *p->data; ++i)
		for (size_t j = 0; j < sizeof *p->data / sizeof **p->data; ++j)
			p->data[i][j] /= d;
}

static const struct mul_impl mat_mul = {
	.mul = mat_mul_mul,
	.div = mat_mul_div,
};

struct mat *mkmat(double aa, double ab, double ac, double ba, double bb,
		double bc, double ca, double cb, double cc)
{
	struct priv *p = malloc(sizeof *p);
	*p = (struct priv){
		.data = {
			{aa, ab, ac},
			{ba, bb, bc},
			{ca, cb, cc},
		},
		.mat = {
			.add = {
				.impl = &mat_add,
			},
			.mul = {
				.impl = &mat_mul,
			},
		},
	};
	return &p->mat;
}

void rmmat(struct mat *m)
{
	free(mattopriv(m));
}

void pmats(struct mat *m, const char *n)
{
	struct priv *p = mattopriv(m);
	printf("(struct mat *)%p\"%s\":\n", (void *)m, n);
	for (size_t i = 0; i < sizeof p->data / sizeof *p->data; ++i) {
		printf("\t{");
		for (size_t j = 0; j < sizeof *p->data / sizeof **p->data; ++j)
			printf("%lf,", p->data[i][j]);
		puts("},");
	}
}
