#include "add.h"
#include "mat.h"
#include "mul.h"

int main()
{
	struct mat *m1 = mkmat(1, 2, 3, 4, 5, 6, 7, 8, 9);
	pmat(m1);
	mul_div(&m1->mul, 2);
	pmat(m1);
	struct mat *m2 = mkmat(9, 8, 7, 6, 5, 4, 3, 2, 1);
	pmat(m2);
	add_sub(&m1->add, &m2->add);
	pmat(m1);
	rmmat(m1);
	rmmat(m2);
	return 0;
}
