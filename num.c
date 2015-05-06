#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "eq.h"
#include "fmt.h"
#include "num.h"
#include "ord.h"

struct priv {
	int value;
	struct num num;
};
#define numtopriv(n) ((struct priv *)((char *)(n) - offsetof(struct priv, num)))
#define eqtopriv(e) numtopriv(((char *)(e) - offsetof(struct num, eq)))
#define ordtopriv(o) numtopriv(((char *)(o) - offsetof(struct num, ord)))
#define fmttopriv(f) numtopriv(((char *)(f) - offsetof(struct num, fmt)))

static int num_cmp(const struct eq *ea, const struct ord *oa,
		const struct eq *eb, const struct ord *ob)
{
	(void)ea, (void)eb;
	return ordtopriv(oa)->value - ordtopriv(ob)->value;
}

static int num_fmt(const struct fmt *f, char *buf, size_t len)
{
	return snprintf(buf, len, "%d", fmttopriv(f)->value);
}

struct num *num_new(int value)
{
	static const struct eq_impl eq_impl = {
		EQ_IMPL_DEFAULTS,
	};
	static const struct ord_impl ord_impl = {
		ORD_IMPL_DEFAULTS,
		._cmp = num_cmp,
	};
	static const struct fmt_impl fmt_impl = {
		FMT_IMPL_DEFAULTS,
		._fmt = num_fmt,
	};
	struct priv *p = malloc(sizeof *p);
	*p = (struct priv){
		.value = value,
		.num = {
			.eq = {.impl = &eq_impl},
			.ord = {.impl = &ord_impl},
			.fmt = {.impl = &fmt_impl},
		},
	};
	return &p->num;
}

void num_free(struct num *n)
{
	free(numtopriv(n));
}
