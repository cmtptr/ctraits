#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cat.h"
#include "eq.h"
#include "fmt.h"
#include "ord.h"

struct priv {
	const char *name;
	unsigned int age;
	struct cat cat;
};
#define cattopriv(c) ((struct priv *)((char *)(c) - offsetof(struct priv, cat)))
#define eqtopriv(e) cattopriv(((char *)(e) - offsetof(struct cat, eq)))
#define ordtopriv(o) cattopriv(((char *)(o) - offsetof(struct cat, ord)))
#define fmttopriv(f) cattopriv(((char *)(f) - offsetof(struct cat, fmt)))

static int cat_cmp(const struct eq *ea, const struct ord *oa,
		const struct eq *eb, const struct ord *ob)
{
	(void)ea, (void)eb;
	assert(oa->impl == ob->impl);
	return strcmp(ordtopriv(oa)->name, ordtopriv(ob)->name);
}

static int cat_fmt(const struct fmt *f, char *buf, size_t len)
{
	const struct priv *p = fmttopriv(f);
	return snprintf(buf, len, "cat(\"%s\", %u)", p->name, p->age);
}

struct cat *cat_new(const char *name, unsigned int age)
{
	static const struct eq_impl cateq = {
		EQ_IMPL_DEFAULTS,
	};
	static const struct ord_impl catord = {
		ORD_IMPL_DEFAULTS,
		._cmp = cat_cmp,
	};
	static const struct fmt_impl catfmt = {
		FMT_IMPL_DEFAULTS,
		._fmt = cat_fmt,
	};
	struct priv *p = malloc(sizeof *p);
	*p = (struct priv){
		.name = name,
		.age = age,
		.cat = {
			.eq = {.impl = &cateq},
			.ord = {.impl = &catord},
			.fmt = {.impl = &catfmt},
		},
	};
	return &p->cat;
}

void cat_free(struct cat *c)
{
	free(cattopriv(c));
}
