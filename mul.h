#ifndef MUL_H
#define MUL_H

struct mul {
	const struct mul_impl *impl;
};

struct mul_impl {
	void (*mul)(struct mul *, double);
	void (*div)(struct mul *, double);
};

void mul_mul(struct mul *, double);
void mul_div(struct mul *, double);

#endif
