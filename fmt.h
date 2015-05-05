#ifndef FMT_H
#define FMT_H

#include <stdlib.h>

struct fmt {
	const struct fmt_impl *impl;
};

struct fmt_impl {
	int (*fmt)(const struct fmt *, char *, size_t);
};

int fmt(const struct fmt *, char *, size_t);
#define FMT_IMPL_DEFAULTS .fmt = fmt

int fmt_print(const char *, ...);

#endif
