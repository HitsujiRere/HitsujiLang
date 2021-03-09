CC=gcc
CFLAGS=-std=c11 -O0 -g -static -Wall -Wextra

CXX=g++
CXXFLAGS=-std=c17 -O2 -Wall -Wextra
SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:.c=.o)

build: $(OBJS)
		$(CXX) -o HitsujiLang $(OBJS) $(LDFLAGS)

$(OBJS): src/HitsujiLang.hpp

test: HitsujiLang
		./test/test.sh

clean:
		rm -f HitsujiLang src/*.o *.o tmp tmp.s

.PHONY: test clean
