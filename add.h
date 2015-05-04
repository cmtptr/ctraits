#ifndef ADD_H
#define ADD_H

struct add {
	const struct add_impl *impl;
};

struct add_impl {
	void (*add)(struct add *, struct add *);
	void (*sub)(struct add *, struct add *);
};

void add_add(struct add *, struct add *);
void add_sub(struct add *, struct add *);

#endif
