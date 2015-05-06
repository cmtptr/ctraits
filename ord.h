#ifndef ORD_H
#define ORD_H

struct ord {
	const struct ord_impl *impl;
};

struct ord_impl {
	int (*_cmp)(const struct eq *, const struct ord *, const struct eq *,
			const struct ord *);
	int (*_lt)(const struct eq *, const struct ord *, const struct eq *,
			const struct ord *);
	int (*_le)(const struct eq *, const struct ord *, const struct eq *,
			const struct ord *);
	int (*_gt)(const struct eq *, const struct ord *, const struct eq *,
			const struct ord *);
	int (*_ge)(const struct eq *, const struct ord *, const struct eq *,
			const struct ord *);
	struct ord *(*_max)(const struct eq *, const struct ord *,
			const struct eq *, const struct ord *);
	struct ord *(*_min)(const struct eq *, const struct ord *,
			const struct eq *, const struct ord *);
};

static inline int cmp(const struct eq *ea, const struct ord *oa,
		const struct eq *eb, const struct ord *ob)
{
	return oa->impl->_cmp(ea, oa, eb, ob);
}
#define cmp(a, b) ((void)(&(a) == &(b)), cmp(&(a)->eq, &(a)->ord, &(b)->eq, &(b)->ord))

static inline int lt(const struct eq *ea, const struct ord *oa,
		const struct eq *eb, const struct ord *ob)
{
	return oa->impl->_lt(ea, oa, eb, ob);
}
#define lt(a, b) ((void)(&(a) == &(b)), lt(&(a)->eq, &(a)->ord, &(b)->eq, &(b)->ord))

static inline int le(const struct eq *ea, const struct ord *oa,
		const struct eq *eb, const struct ord *ob)
{
	return oa->impl->_le(ea, oa, eb, ob);
}
#define le(a, b) ((void)(&(a) == &(b)), le(&(a)->eq, &(a)->ord, &(b)->eq, &(b)->ord))

static inline int gt(const struct eq *ea, const struct ord *oa,
		const struct eq *eb, const struct ord *ob)
{
	return oa->impl->_gt(ea, oa, eb, ob);
}
#define gt(a, b) ((void)(&(a) == &(b)), gt(&(a)->eq, &(a)->ord, &(b)->eq, &(b)->ord))

static inline int ge(const struct eq *ea, const struct ord *oa,
		const struct eq *eb, const struct ord *ob)
{
	return oa->impl->_ge(ea, oa, eb, ob);
}
#define ge(a, b) ((void)(&(a) == &(b)), ge(&(a)->eq, &(a)->ord, &(b)->eq, &(b)->ord))

static inline struct ord *max(const struct eq *ea, const struct ord *oa,
		const struct eq *eb, const struct ord *ob)
{
	return oa->impl->_max(ea, oa, eb, ob);
}
#define max(a, b) ((void)(&(a) == &(b)), max(&(a)->eq, &(a)->ord, &(b)->eq, &(b)->ord))

static inline struct ord *min(const struct eq *ea, const struct ord *oa,
		const struct eq *eb, const struct ord *ob)
{
	return oa->impl->_min(ea, oa, eb, ob);
}
#define min(a, b) ((void)(&(a) == &(b)), min(&(a)->eq, &(a)->ord, &(b)->eq, &(b)->ord))

int ord_cmp(const struct eq *, const struct ord *, const struct eq *,
		const struct ord *);
int ord_lt(const struct eq *, const struct ord *, const struct eq *,
		const struct ord *);
int ord_le(const struct eq *, const struct ord *, const struct eq *,
		const struct ord *);
int ord_gt(const struct eq *, const struct ord *, const struct eq *,
		const struct ord *);
int ord_ge(const struct eq *, const struct ord *, const struct eq *,
		const struct ord *);
struct ord *ord_max(const struct eq *, const struct ord *, const struct eq *,
		const struct ord *);
struct ord *ord_min(const struct eq *, const struct ord *, const struct eq *,
		const struct ord *);
#define ORD_IMPL_DEFAULTS ._cmp = ord_cmp, ._lt = ord_lt, ._le = ord_le,\
	._gt = ord_gt, ._ge = ord_ge, ._max = ord_max, ._min = ord_min

#endif
