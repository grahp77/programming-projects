CFLAGS = -Wall -Werror -Wextra -std=c11 -g -fprofile-arcs -ftest-coverage -I/usr/include
NCURSES = -lncurses
BACK = brick_game/tetris/backend.c
FRONT = gui/cli/frontend.c
MAIN = tetris.c
TEST = test/test.c
TEST_UTILS = test/test_utils.c
TEST_EXEC = test_backend
TEST_OBJS = test/test.o brick_game/tetris/backend.o test/test_utils.o
PDF_FILE = documentation.pdf
VERSION = 1.0
PACKAGE = tetris-$(VERSION)
DIST_FILES = brick_game gui test Doxyfile tetris.h struct.h highscore.txt $(MAIN) Makefile
UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)  # WSL
    BROWSER_OPEN = wslview
	LDFLAGS = -L/usr/lib/x86_64-linux-gnu
else ifeq ($(UNAME), Darwin) # macOS
    BROWSER_OPEN = open
	LDFLAGS = 
else
    BROWSER_OPEN = echo "Unknown OS: Cannot open browser automatically"
	LDFLAGS = 
endif

.PHONY: all build/libtetris.a install uninstall test gcov_report dvi dist clang_format clang_check valgrind clean

all: clean install

clean:
	clear
	rm -rf *.o *.gcda *.gcno $(TEST_EXEC) coverage.info coverage.cleaned.info build/tetris
	rm -rf brick_game/tetris/*.gcda brick_game/tetris/*.gcno brick_game/tetris/*.o test/*.gcda test/*.gcno test/*.o
	rm -rf doc
	rm -rf build
	rm -rf coverage
	rm -rf gcov_report

build/libtetris.a: $(BACK)
	mkdir -p build
	gcc $(CFLAGS) -c $(BACK)
	ar rcs build/libbac.a backend.o
	mv *.o build

install: test clean build/libtetris.a 
	gcc $(CFLAGS) $(MAIN) build/*.a $(FRONT) $(NCURSES) -o build/tetris $(LDFLAGS) && ./build/tetris

test: $(TEST_OBJS)
	gcc $(CFLAGS) $(TEST_OBJS) -lcheck -lm -o $(TEST_EXEC)
	./$(TEST_EXEC)

test/test.o: test/test.c
	gcc $(CFLAGS) -c test/test.c -o test/test.o

brick_game/tetris/backend.o: brick_game/tetris/backend.c
	gcc $(CFLAGS) -c brick_game/tetris/backend.c -o brick_game/tetris/backend.o

test/test_utils.o: test/test_utils.c
	gcc $(CFLAGS) -c test/test_utils.c -o test/test_utils.o

uninstall:
	rm -f tetris

dvi: clean
	doxygen Doxyfile
	$(BROWSER_OPEN) doc/html/index.html

dist:
	mkdir -p $(PACKAGE)
	cp -r $(DIST_FILES) $(PACKAGE)
	tar -czvf $(PACKAGE).tar.gz $(PACKAGE)
	rm -rf $(PACKAGE)
	echo "Archive created!"

clang_format: 
	cp ../materials/linters/.clang-format .
	find . -type f -name "*.c" -exec clang-format -n {} \;
	rm -rf .clang-format

gcov_report: clean test
	lcov -t "Report" -c -d . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	@echo "Coverage report generated in gcov_report/index.html"
	$(BROWSER_OPEN) gcov_report/index.html