#ifndef EQ_H
#define EQ_H

struct eq {
	const struct eq_impl *impl;
};

struct eq_impl {
	int (*eq)(const struct eq *, const struct eq *);
	int (*neq)(const struct eq *, const struct eq *);
};

int eq(const struct eq *, const struct eq *);
int neq(const struct eq *, const struct eq *);
#define EQ_IMPL_DEFAULTS .eq = eq, .neq = neq

#endif
