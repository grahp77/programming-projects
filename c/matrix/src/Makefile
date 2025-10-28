TARGET = s21_matrix.a
GCC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TESTFLAGS = -fprofile-arcs -ftest-coverage
SRC = $(wildcard library/*.c)
TEST_SRC = $(wildcard test/*.c)
OS:= $(shell uname)

ifeq ($(OS), Darwin)
	LDFLAGS = -lcheck
else ifeq ($(OS), Linux)
	LDFLAGS = -lcheck -lsubunit -lm
endif

$(TARGET):
	@mkdir -p objects
	@$(GCC) $(CFLAGS) -c $(SRC)
	@mv *.o objects/
	@ar rcs $(TARGET) objects/*.o
	@rm -rf objects
	
all: clean $(TARGET) test gcov_report

test: $(TARGET)
	@mkdir -p test
	@$(GCC) $(CFLAGS) $(TESTFLAGS) $(SRC) $(TEST_SRC) $(TARGET) $(LDFLAGS)  --coverage -o ./test/test_file
	@./test/test_file

gcov_report: test
	lcov --capture --directory . --output-file coverage.info --rc geninfo_unexecuted_blocks=1
	genhtml -o report/ coverage.info
	rm -rf *.gcno *.gcov *.gcda *.info *.a tests/*.o
	open ./report/index.html || xdg-open ./report/index.html
git:
	git add .
	git commit -m "Auto-commit"
	git push --set-upstream origin develop

clang:
	clang-format -n ./*/*.c *.h

clean:
	@rm -rf *.o s21_matrix.a
	@rm -rf test/*log test/test* report