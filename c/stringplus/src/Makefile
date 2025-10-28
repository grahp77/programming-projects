CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = --coverage
CHECK_FLAGS = -lcheck -lm -lsubunit
STATIC_LIB = s21_string.a
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
TESTS_SRC = tests/tests.c

SHELLNAME := $(shell uname)
ifeq ($(SHELLNAME), Linux)
	LIB = -L. -l$(STATIC_LIB)
else ifeq ($(SHELLNAME), Darwin)
	LIB =
	CHECK_FLAGS = -lcheck -lm
endif

all: $(STATIC_LIB) test

clean:
	rm -rf *.o *.a report $(FILES_REPORT) test *.gcno *.gcda *.gcov gcov_test gcov_test_lcov report_gcov report_lcov coverage.info

test: $(STATIC_LIB)
	$(CC) $(CFLAGS) $(TESTS_SRC) -L. $(STATIC_LIB) $(CHECK_FLAGS) -o test
	./test

s21_string.a: $(OBJ)
	ar rcs $(STATIC_LIB) $(OBJ)
	rm -f *.o

gcov_report:
	$(CC) $(CFLAGS) $(TESTS_SRC) $(SRC) $(CHECK_FLAGS) $(GCOV_FLAGS) -o gcov_test
	./gcov_test
	mkdir -p report_gcov
	gcovr --html-details -o ./report_gcov/report.html
	rm -f *.gcno *.gcda

gcov_report_lcov:
	$(CC) $(CFLAGS) $(TESTS_SRC) $(SRC) $(CHECK_FLAGS) $(GCOV_FLAGS) -o gcov_test_lcov
	./gcov_test_lcov
	lcov --capture --directory . --output-file coverage.info --rc branch_coverage=1
	genhtml --branch-coverage coverage.info --output-directory report_lcov
	rm -f *.gcno *.gcda

valg:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test
