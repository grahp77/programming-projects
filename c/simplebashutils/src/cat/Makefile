FLAGS = -Wall -Werror -Wextra -std=c11
SRC = s21_cat.c
OBJ = s21_cat

s21_cat: s21_cat.c
	gcc $(FLAGS) $(SRC) -o $(OBJ)
	

clean: 
	rm -rf $(OBJ)	

rebuild: clean $(OBJ)

test:
	bash test_cat.sh