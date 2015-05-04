#ifndef MAT_H
#define MAT_H

#include "add.h"
#include "mul.h"

struct mat {
	struct add add;
	struct mul mul;
};

struct mat *mkmat(double, double, double, double, double, double, double,
		double, double);
void rmmat(struct mat *);
void pmats(struct mat *, const char *);
#define pmat(m) pmats(m, #m)

#endif
