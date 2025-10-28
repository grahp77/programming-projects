LIBRARY = s21_decimal.a

SRCS = $(wildcard *.c)
HEADERS = $(SRCS:.c=.h)
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
#LDFLAGS = -lcheck -lm -pthread --coverage
LDFLAGS = -lcheck -lm -lrt -pthread -lsubunit --coverage

all: $(LIBRARY)

$(LIBRARY): $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

TEST_SRCS = $(filter-out tests/s21_tests_main.c, $(wildcard tests/*.c))
TEST_OBJS = $(TEST_SRCS:.c=.o)

test: $(TEST_OBJS) $(LIBRARY)
	$(CC) $(CFLAGS) tests/s21_tests_main.c $(TEST_OBJS) $(LIBRARY) -o run_test $(LDFLAGS)
	./run_test

gcov_report: CFLAGS += --coverage
gcov_report: clean $(LIBRARY)
	$(CC) $(CFLAGS) $(SRCS) tests/s21_tests_main.c $(TEST_SRCS) -o run_test_with_gcov $(LDFLAGS)
	./run_test_with_gcov
	lcov -t "Report" -c -d . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	@echo "Coverage report generated in gcov_report/index.html"

clean:
	rm -f $(OBJS) $(LIBRARY) run_test run_test_with_gcov
	rm -rf gcov_report coverage.info
	rm -f tests/*.o
	rm -rf *.gcno *.gcov *.gcda
	rm -rf report/

.PHONY: all clean test gcov_report
