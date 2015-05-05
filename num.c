#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "eq.h"
#include "num.h"
#include "ord.h"

struct priv {
	int value;
	struct num num;
};
#define numtopriv(n) ((struct priv *)((char *)(n) - offsetof(struct priv, num)))
#define ordtopriv(o) numtopriv(((char *)(o) - offsetof(struct num, ord)))
#define fmttopriv(f) numtopriv(((char *)(f) - offsetof(struct num, fmt)))

static int num_cmp(const struct ord *a, const struct ord *b)
{
	assert(a->impl == b->impl);
	return ordtopriv(a)->value - ordtopriv(b)->value;
}

static int num_fmt(const struct fmt *f, char *buf, size_t len)
{
	return snprintf(buf, len, "%d", fmttopriv(f)->value);
}

struct num *num_new(int value)
{
	static const struct eq_impl ceq = {
		EQ_IMPL_DEFAULTS,
	};
	static const struct ord_impl cord = {
		ORD_IMPL_DEFAULTS,
		.cmp = num_cmp,
	};
	static const struct fmt_impl cfmt = {
		FMT_IMPL_DEFAULTS,
		.fmt = num_fmt,
	};
	struct priv *p = malloc(sizeof *p);
	*p = (struct priv){
		.value = value,
		.num = {
			.ord = {
				.eq = {
					.impl = &ceq,
				},
				.impl = &cord,
			},
			.fmt = {
				.impl = &cfmt,
			},
		},
	};
	return &p->num;
}

void num_free(struct num *n)
{
	free(numtopriv(n));
}
