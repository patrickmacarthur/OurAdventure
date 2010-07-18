# vim: set noexpandtab shiftwidth=8 tabstop=8:
# 
# cs516/a3/tests/Makefile
#
# Makefile - file to make and runs tests

CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS =

TESTS =	 dir dirlist adj room start map door lockeddoor
all:	test

test:	$(TESTS)

$(TESTS):
	-$(MAKE) -C $@ test

clean:
	-for i in $(TESTS); do $(MAKE) -C $$i clean; done

.PHONY: all test $(TESTS)
