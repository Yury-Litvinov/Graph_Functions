#.PHONY: all build rebuild clean test cppcheck linter git
CC=gcc
AR=ar rc
CFLAGS=-c -Wall -Werror -Wextra
LDFLAGS=
SOURCES=graph.c graph.h input_parse.c input_parse.h conditions.c conditions.h pn.c pn.h stack.c stack.h
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=

all: build

build: graph

rebuild: clean build

clean:
	rm -rf $(OBJECTS)

test: linter cppcheck

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SOURCES)

linter:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c $(SOURCES)

git:
	git add $(SOURCES) Makefile
	git status

graph: 
	$(CC) $(FLAGS) graph.c input_parse.c conditions.c pn.c stack.c -o ../build/graph
#	../build/graph
