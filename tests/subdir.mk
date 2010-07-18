# tests/subdir.mk
#
# subdir.mk - File containing default script for test subdirectories
#
# Include this file at the top of the makefile for the tests.

include ../../objects.mk
VPATH = ../..

test: all
	@echo Sample input:
	@echo -------------
	@cat sample.in
	@echo
	@echo Test Run:
	@echo -------------
	@./a.out 2>&1 < sample.in

all: a.out

a.out: test.o
	$(CXX) $(LDFLAGS) -o a.out test.o $(patsubst %,../../%,$(subst ' ', ,$(OBJECTS)))

clean:
	$(RM)	*.o a.out

.PHONY: test all clean a.out

# vim: set ft=make noet sw=8 ts=8:
