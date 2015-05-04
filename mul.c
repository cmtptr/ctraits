#include <stdio.h>

#include "mul.h"

void mul_mul(struct mul *m, double d)
{
	printf("%p * %lf\n", (void *)m, d);
	m->impl->mul(m, d);
}

void mul_div(struct mul *m, double d)
{
	printf("%p / %lf\n", (void *)m, d);
	m->impl->div(m, d);
}
