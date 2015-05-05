#include "ord.h"

int cmp(const struct ord *a, const struct ord *b)
{
	if (a->eq.impl->eq(&a->eq, &b->eq))
		return 0;
	return a < b ? -1 : 1;
}

int lt(const struct ord *a, const struct ord *b)
{
	return a->impl->cmp(a, b) < 0;
}

int le(const struct ord *a, const struct ord *b)
{
	return a->impl->cmp(a, b) <= 0;
}

int gt(const struct ord *a, const struct ord *b)
{
	return a->impl->cmp(a, b) > 0;
}

int ge(const struct ord *a, const struct ord *b)
{
	return a->impl->cmp(a, b) >= 0;
}

struct ord *max(const struct ord *a, const struct ord *b)
{
	return (struct ord *)(a->impl->ge(a, b) ? a : b);
}

struct ord *min(const struct ord *a, const struct ord *b)
{
	return (struct ord *)(a->impl->le(a, b) ? a : b);
}
