#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cat.h"
#include "eq.h"
#include "ord.h"

struct priv {
	const char *name;
	unsigned int age;
	struct cat cat;
};
#define cattopriv(c) ((struct priv *)((char *)(c) - offsetof(struct priv, cat)))
#define ordtopriv(o) cattopriv(((char *)(o) - offsetof(struct cat, ord)))
#define fmttopriv(f) cattopriv(((char *)(f) - offsetof(struct cat, fmt)))

static int cat_cmp(const struct ord *a, const struct ord *b)
{
	assert(a->impl == b->impl);
	return strcmp(ordtopriv(a)->name, ordtopriv(b)->name);
}

static int cat_fmt(const struct fmt *f, char *buf, size_t len)
{
	const struct priv *p = fmttopriv(f);
	return snprintf(buf, len, "cat(\"%s\", %u)", p->name, p->age);
}

struct cat *cat_new(const char *name, unsigned int age)
{
	static const struct eq_impl ceq = {
		EQ_IMPL_DEFAULTS,
	};
	static const struct ord_impl cord = {
		ORD_IMPL_DEFAULTS,
		.cmp = cat_cmp,
	};
	static const struct fmt_impl cfmt = {
		FMT_IMPL_DEFAULTS,
		.fmt = cat_fmt,
	};
	struct priv *p = malloc(sizeof *p);
	*p = (struct priv){
		.name = name,
		.age = age,
		.cat = {
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
	return &p->cat;
}

void cat_free(struct cat *c)
{
	free(cattopriv(c));
}
