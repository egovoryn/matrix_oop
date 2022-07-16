CC=g++ -std=c++17 -Wall -Werror -Wextra -pedantic
CHECKFLAGS=-lgtest
REPORTDIR=report
GCOV=--coverage 

all: test

matrix_oop.a:
	$(CC) -c matrix_oop.cpp -o matrix_oop.o
	ar rcs matrix_oop.a matrix_oop.o

test: clean matrix_oop.a
	$(CC) $(GCOV) -c matrix_oop.cpp 
	$(CC) -c matrix_test.cpp $(CHECKFLAGS)
	$(CC) $(GCOV) -o matrix_test matrix_test.o matrix_oop.o $(CHECKFLAGS)
	./matrix_test

check:
	cppcheck *.cpp && cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ *.h

leaks: test
	leaks -atExit -- ./matrix_test

gcov_report:
	lcov -t "Unit-tests of matrix_oop" -o matrix_oop.info -c -d .
	genhtml -o $(REPORTDIR) matrix_oop.info
	open -a "Safari" ./report/index.html

clean:
	rm -rf ./*.o ./*.a ./a.out ./*.gcno ./*.gcda ./report *.info ./*.info report matrix_test matrix_oop