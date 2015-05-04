#include <stdio.h>

#include "add.h"

void add_add(struct add *a1, struct add *a2)
{
	printf("%p + %p\n", (void *)a1, (void *)a2);
	a1->impl->add(a1, a2);
}

void add_sub(struct add *a1, struct add *a2)
{
	printf("%p - %p\n", (void *)a1, (void *)a2);
	a1->impl->sub(a1, a2);
}
