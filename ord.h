#ifndef ORD_H
#define ORD_H

#include "eq.h"

struct ord {
	struct eq eq;
	const struct ord_impl *impl;
};

struct ord_impl {
	int (*cmp)(const struct ord *, const struct ord *);
	int (*lt)(const struct ord *, const struct ord *);
	int (*le)(const struct ord *, const struct ord *);
	int (*gt)(const struct ord *, const struct ord *);
	int (*ge)(const struct ord *, const struct ord *);
	struct ord *(*max)(const struct ord *, const struct ord *);
	struct ord *(*min)(const struct ord *, const struct ord *);
};

int cmp(const struct ord *, const struct ord *);
int lt(const struct ord *, const struct ord *);
int le(const struct ord *, const struct ord *);
int gt(const struct ord *, const struct ord *);
int ge(const struct ord *, const struct ord *);
struct ord *max(const struct ord *, const struct ord *);
struct ord *min(const struct ord *, const struct ord *);
#define ORD_IMPL_DEFAULTS .cmp = cmp, .lt = lt, .le = le, .gt = gt, .ge = ge,\
	.max = max, .min = min

#endif
