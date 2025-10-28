CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror
GTEST_FLAGS := -lgtest -lgtest_main -pthread
GCOV_FLAGS := -fprofile-arcs -ftest-coverage

LIB_SRCS := lib/*.cc
TEST_SRC := tests/Unit-test.cc
OBJ_DIR := obj
REPORT_DIR := report

.PHONY: all clean test s21_matrix_oop.a gcov_report

all: s21_matrix_oop.a test

s21_matrix_oop.a: | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I. -c $(LIB_SRCS)
	mv *.o $(OBJ_DIR)/
	ar rcs $@ $(OBJ_DIR)/*.o
	ranlib $@

test: s21_matrix_oop.a
	$(CXX) $(CXXFLAGS) -I. $(TEST_SRC) s21_matrix_oop.a $(GTEST_FLAGS) -o $(OBJ_DIR)/matrix_test
	./$(OBJ_DIR)/matrix_test

gcov_report: clean
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) -I. $(TEST_SRC) $(LIB_SRCS) $(GTEST_FLAGS) -o matrix_test
	./matrix_test
	lcov -c -d . -o coverage.info --ignore-errors inconsistent
	lcov -e coverage.info "*/lib/*" -o filtered.info --ignore-errors unused 2>/dev/null || true
	genhtml filtered.info -o report
	open report/index.html 2>/dev/null || echo "Open report/index.html manually"
	rm -f coverage.info filtered.info matrix_test

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(REPORT_DIR):
	mkdir -p $(REPORT_DIR)

clean:
	rm -rf $(OBJ_DIR) $(REPORT_DIR)
	rm -f *.a *.gcno *.gcda *.gcov matrix_test