#ifndef CAT_H
#define CAT_H

#include "fmt.h"
#include "ord.h"

struct cat {
	struct ord ord;
	struct fmt fmt;
};

struct cat *cat_new(const char *, unsigned int);
void cat_free(struct cat *);

#endif
