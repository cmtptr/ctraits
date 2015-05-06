#include "eq.h"

int eq_eq(const struct eq *a, const struct eq *b)
{
	return a == b;
}

int eq_neq(const struct eq *a, const struct eq *b)
{
	return !a->impl->_eq(a, b);
}
