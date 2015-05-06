#ifndef FMT_H
#define FMT_H

#include <stdlib.h>

struct fmt {
	const struct fmt_impl *impl;
};

struct fmt_impl {
	int (*_fmt)(const struct fmt *, char *, size_t);
};

int fmt_fmt(const struct fmt *, char *, size_t);
#define FMT_IMPL_DEFAULTS ._fmt = fmt_fmt

int fmt_print(const char *, ...);

#endif
