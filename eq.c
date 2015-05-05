#include "eq.h"

int eq(const struct eq *a, const struct eq *b)
{
	return a == b;
}

int neq(const struct eq *a, const struct eq *b)
{
	return !a->impl->eq(a, b);
}
