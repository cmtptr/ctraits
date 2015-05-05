#ifndef NUM_H
#define NUM_H

#include "fmt.h"
#include "ord.h"

struct num {
	struct ord ord;
	struct fmt fmt;
};

struct num *num_new(int);
void num_free(struct num *);

#endif
