#ifndef EQ_H
#define EQ_H

struct eq {
	const struct eq_impl *impl;
};

struct eq_impl {
	int (*_eq)(const struct eq *, const struct eq *);
	int (*_neq)(const struct eq *, const struct eq *);
};

static inline int eq(const struct eq *a, const struct eq *b)
{
	return a->impl->_eq(a, b);
}
#define eq(a, b) ((void)(&(a) == &(b)), eq(&(a)->eq, &(b)->eq))

static inline int neq(const struct eq *a, const struct eq *b)
{
	return a->impl->_neq(a, b);
}
#define neq(a, b) ((void)(&(a) == &(b)), neq(&(a)->eq, &(b)->eq))

int eq_eq(const struct eq *, const struct eq *);
int eq_neq(const struct eq *, const struct eq *);
#define EQ_IMPL_DEFAULTS ._eq = eq_eq, ._neq = eq_neq

#endif
