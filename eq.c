#include <assert.h>

#include "eq.h"

int eq_eq(const struct eq *a, const struct eq *b)
{
	assert(a->impl == b->impl);
	return a == b;
}

int eq_neq(const struct eq *a, const struct eq *b)
{
	return !a->impl->_eq(a, b);
}
