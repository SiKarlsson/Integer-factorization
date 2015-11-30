CC=g++
CFLAGS=-Wall -Wextra -std=c++11
DFLAGS=-DDEBUG=true -g
PFLAGS=-O3
SPFLAGS=-m32 -Wno-literal-suffix
PROGNAME=main

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    CC=clang++
endif

default: local

clean:
	rm local.cpp localfiles.h spoj.cpp spojfiles.h min.cpp incl.h

incl:
	@echo "Compiling ttmath header..."
	@cpp -m32 -P -nostdinc ttmath/ttmathuint.h | ./minify.sh > incl.h
	@echo "\n#pragma GCC diagnostic pop" >> incl.h

spojfiles: incl
	@echo "Compiling spoj header..."
	#@cat common.h spoj.h incl.h > spojfiles.h
	@cat incl.h > spojfiles.h

spoj: spojfiles main.cpp
	@echo "Compiling spoj (32 bit) file..."
	@cpp -m32 -P -nostdinc main.cpp | ./minify.sh > min.cpp
	@cat spojfiles.h min.cpp > spoj.cpp
	$(CC) $(CFLAGS) $(PFLAGS) $(SPFLAGS) -o $(PROGNAME) spoj.cpp

localfiles:
	@echo "Compiling local header..."
	#@cat common.h local.h > localfiles.h

local: localfiles main.cpp
	@echo "Compiling local (64 bit) file..."
	#@cat localfiles.h main.cpp > local.cpp
	@cat main.cpp > local.cpp
	$(CC) $(CFLAGS) $(PFLAGS) -o $(PROGNAME) local.cpp

debug:
	$(CC) $(CFLAGS) $(DFLAGS) -o $(PROGNAME) $(PROGNAME).cpp
