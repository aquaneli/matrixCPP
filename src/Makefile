CC = gcc -std=c++17 -g
FLAGS = -Wall -Werror -Wextra
OS = $(shell uname)
LIBSOURCES = matrix_oop.cc matrix_oop_tests.cc

ifeq ($(OS), Linux)
	CHECKFLAGS=-lgtest -lgtest_main -lrt -lm -lstdc++ -pthread -fprofile-arcs -ftest-coverage
else
	CHECKFLAGS=-lgtest -lgtest_main -lm -lpthread -fprofile-arcs -ftest-coverage -lstdc++
endif

all: test
	

matrix_oop.a:
	$(CC) $(FLAGS) -c matrix_oop.cc
	ar -crs libmatrix_oop.a matrix_oop.o

test:
	$(CC) $(FLAGS) $(LIBSOURCES) -o run $(CHECKFLAGS) -lgcov --coverage
	./run

gcov_report: test
	lcov --no-external -t "test" -o report.info -c -d .
	genhtml -o report report.info
	open ./report/index.html

test_leaks: test
	leaks --atExit -- ./run

valgrind:
	$(CC) $(FLAGS) $(LIBSOURCES) -o vtests_run $(CHECKFLAGS) -lgcov --coverage
	sh valgrind.sh ./vtests_run

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -style=Google -n matrix_oop.* matrix_oop_tests.cc

clean:
	rm -rf report \
	libmatrix_oop.a \
	report.info \
	matrix_oop.gcda \
	matrix_oop.gcno \
	matrix_oop_tests.gcda \
	matrix_oop_tests.gcno \
	matrix_oop.o \
	run.dSYM \
	run