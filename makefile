CFLAGS ?= -O2 -pipe
CFLAGS += -std=c11
CPPFLAGS += -pedantic -Wall -Werror -Wextra -Wno-override-init

sources := add.c ctraits.c mat.c mul.c
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
