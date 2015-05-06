#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fmt.h"

int fmt_fmt(const struct fmt *f, char *dest, size_t len)
{
	return snprintf(dest, len, "%p", (void *)f);
}

int fmt_print(const char *fmt, ...)
{
	char *buf = malloc(BUFSIZ), *ptr = buf;
	size_t len = BUFSIZ;
	va_list ap;
	va_start(ap, fmt);
	const char *str;
	while (str = strstr(fmt, "{}"), str) {
		size_t l = str - fmt;
		memcpy(ptr, fmt, l);
		fmt = str + 2;
		ptr += l, len -= l;
		const struct fmt *f = va_arg(ap, struct fmt *);
		l = f->impl->_fmt(f, ptr, len);
		ptr += l, len -= l;
	}
	len = strncpy(ptr, fmt, len) - buf;
	fputs(buf, stdout);
	va_end(ap);
	free(buf);
	return len;
}
