#include "eq.h"
#include "ord.h"

int ord_cmp(const struct eq *ea, const struct ord *oa, const struct eq *eb,
		const struct ord *ob)
{
	if (ea->impl->_eq(ea, eb))
		return 0;
	return oa < ob ? -1 : 1;
}

int ord_lt(const struct eq *ea, const struct ord *oa, const struct eq *eb,
		const struct ord *ob)
{
	return oa->impl->_cmp(ea, oa, eb, ob) < 0;
}

int ord_le(const struct eq *ea, const struct ord *oa, const struct eq *eb,
		const struct ord *ob)
{
	return oa->impl->_cmp(ea, oa, eb, ob) <= 0;
}

int ord_gt(const struct eq *ea, const struct ord *oa, const struct eq *eb,
		const struct ord *ob)
{
	return oa->impl->_cmp(ea, oa, eb, ob) > 0;
}

int ord_ge(const struct eq *ea, const struct ord *oa, const struct eq *eb,
		const struct ord *ob)
{
	return oa->impl->_cmp(ea, oa, eb, ob) >= 0;
}

struct ord *ord_max(const struct eq *ea, const struct ord *oa,
		const struct eq *eb, const struct ord *ob)
{
	return (struct ord *)(oa->impl->_ge(ea, oa, eb, ob) ? oa : ob);
}

struct ord *ord_min(const struct eq *ea, const struct ord *oa,
		const struct eq *eb, const struct ord *ob)
{
	return (struct ord *)(oa->impl->_le(ea, oa, eb, ob) ? oa : ob);
}
