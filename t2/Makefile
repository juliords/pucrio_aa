CPATH=-I.

# .c, .h, .S
RESOURCES=main.c                    \
	  common.c     common.h     \
	  components.c components.h \
	  graph.c      graph.h      \
	  list.c       list.h

SRC=$(filter %.c, ${RESOURCES})
HDR=$(filter %.h, ${RESOURCES})
OBJ=${SRC:.c=.o}

CFLAGS= -O2 -Wall -g $(CPATH)
LDFLAGS=-O2 -lm
EXE=main

.PHONY: all test clean
all: $(EXE)
zip: Makefile $(SRC) $(HDR)
	zip -r mypackage.zip $^

test: $(EXE)
	./$<

$(EXE): .depend.mk $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(EXE)

$(OBJ): %.o: %.c

.depend.mk: $(RESOURCES) Makefile
	$(CC) -MM $(CFLAGS) $(SRC) > .depend.mk

clean:
	rm -f $(EXE) $(OBJ)

-include .depend.mk
