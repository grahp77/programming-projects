FLAGS = -Wall -Werror -Wextra -std=c11 -g
SRC = s21_grep.c
OBJ = s21_grep 
OBJ2 = ../tests/grep_tests/s21_grep
FILE1 = ../tests/grep_tests/input_test2.txt
# FILE2 = ../tests/grep_tests/input_test1.txt
# PATTERN = ../tests/grep_tests/pattern.txt
PATTERN = abc

FLAG = -c

all: clean s21_grep clear
	clear && grep $(FLAG) $(PATTERN) $(FILE1) $(FILE2); ./s21_grep $(FLAG) $(PATTERN) $(FILE1) $(FILE2)

clear: 
	clear

s21_grep: s21_grep.c
	gcc $(FLAGS) $(SRC) -o $(OBJ) 	 
	cp -f s21_grep ../tests/grep_tests 


clean: 
	rm -rf $(OBJ) $(OBJ2)


rebuild: clean $(OBJ)


test:
	cd ../tests/ &&	chmod +x *.py && ./test_grep.py && cd ../grep

push: clean
	git add . ../tests
	git commit -m "next1.3"
	git push origin develop