CPATH=-I.

# .c, .h, .S
RESOURCES=main.c \
	  common.c common.h \
	  instance.c instance.h \
	  heap.c heap.h \
	  quick.c quick.h \
	  stupid.c stupid.h 

SRC=$(filter %.c, ${RESOURCES})
HDR=$(filter %.h, ${RESOURCES})
OBJ=${SRC:.c=.o}

CFLAGS= -O0 -Wall -g $(CPATH)
LDFLAGS=-O0 -lm
EXE=main

.PHONY: all clean
all: .depend.mk $(EXE)
zip: Makefile $(SRC) $(HDR)
	zip -r mypackage.zip $^

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(EXE)

$(OBJ): %.o: %.c

.depend.mk: $(RESOURCES) Makefile
	$(CC) -MM $(CFLAGS) $(SRC) > .depend.mk

clean:
	rm -f $(EXE) $(OBJ)

-include .depend.mk
