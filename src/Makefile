FILES = functions/*.c bonus_functions/*.c sup_functions/*.c
CC = gcc -std=c11
FLAGS = -Wall -Wextra -Werror

all: clean s21_string.a test gcov_report 

s21_string.a:
	$(CC) $(FLAGS) -c $(FILES)
	ar r s21_string.a *.o
	rm *.o

test: 
	$(CC) $(FLAGS) -c $(FILES) -DMAC
	$(CC) $(FLAGS) test.c -o test *.o -pthread -lcheck -pthread -lm -DMAC
	
	# $(CC) $(FLAGS) -c $(FILES) -std=c11 -DLINUX
	# $(CC) $(FLAGS) test.c -o test *.o -pthread -lcheck_pic -pthread -lrt -lm -lsubunit -DLINUX

	rm *.o
	./test

clean:
	-rm -rf *.o *.a test *.gcno *.gcda gcov_test test.info report a.out s21_string.a

gcov_report:
	$(CC) $(FLAGS) -fprofile-arcs -ftest-coverage $(FILES) test.c -pthread -lcheck -pthread -lm -o gcov_test -DMAC
	# $(CC) $(FLAGS) -fprofile-arcs -ftest-coverage $(FILES) test.c -pthread -lcheck_pic -pthread -lrt -lm -lsubunit -o gcov_test -DLINUX
	./gcov_test
	lcov -t "report" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

check_style:
	cp -R ../materials/linters/.clang-format .clang-format
	cp -R ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	clang-format -n $(FILES) test.c
	python3 ../materials/linters/cpplint.py --extensions=c $(FILES) test.c
	rm -rf .clang-format CPPLINT.cfg

set_style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i $(FILES) test.c
	rm .clang-format

git:
	git add $(FILES) ../materials/linters/* Makefile s21_string.h test.c
	git commit -m "v3.0"
	git push origin develop