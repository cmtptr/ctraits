CFLAGS ?= -O2 -pipe
CFLAGS += -std=c11
CPPFLAGS += -pedantic -Wall -Werror -Wextra -Wno-override-init

sources := cat.c ctraits.c eq.c fmt.c num.c ord.c
objects := $(sources:.c=.o)
bin := a.out

.PHONY: all clean
all: $(bin)

clean:
	$(RM) $(objects) $(bin)

.SUFFIXES:
.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(bin): $(objects)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(objects) $(LDADD)

$(objects): makefile
cat.o: cat.c cat.h fmt.h ord.h eq.h
ctraits.o: ctraits.c cat.h fmt.h ord.h eq.h num.h
eq.o: eq.c eq.h
fmt.o: fmt.c fmt.h
num.o: num.c eq.h num.h fmt.h ord.h
ord.o: ord.c ord.h eq.h
