CFLAGS=-g -c -Wall -Wextra -Werror -std=c11 -pedantic
FLAGS=-Wall -Wextra -Werror -std=c11 -pedantic
ASAN=#-fsanitize=address -fanalyzer

all: install

install:
	cmake -S . -B ./build && cd ./build && make

uninstall:
	rm -rf build

clean:
	rm -rf build
	rm -f SmartCalc
	rm -rf SmartCalc_manual
	rm -rf SmartCalc_v1.0
	rm -f SmartCalc_v1.0.tar.gz
	rm -f ./back_tests/*.a ./back_tests/*.o
	rm -f ./back_tests/*.info ./back_tests/*.gcda ./back_tests/*.gcno ./back_tests/*.gcov
	rm -rf ./back_tests/coverage
	rm -f ./back_tests/mytests

dvi: 
	makeinfo --html smartcalc.texi
	open SmartCalc_manual/index.html 

dist:
	mkdir SmartCalc_v1.0
	cp CMakeLists.txt ./SmartCalc_v1.0
	cp Makefile ./SmartCalc_v1.0
	cp -R backend ./SmartCalc_v1.0
	cp -R frontend ./SmartCalc_v1.0
	cp smartcalc.texi ./SmartCalc_v1.0
	tar czvf SmartCalc_v1.0.tar.gz ./SmartCalc_v1.0
	rm -rf SmartCalc_v1.0 

tests:
	cd ./back_tests && \
	rm -f s21_calc.a && \
	gcc $(FLAGS) $(ASAN) -fprofile-arcs -ftest-coverage -o InfixIntoRPN.o -c ../backend/InfixIntoRPN.c && \
	gcc $(FLAGS) $(ASAN) -fprofile-arcs -ftest-coverage -o RPNeval.o -c ../backend/RPNeval.c && \
	gcc $(FLAGS) $(ASAN) -fprofile-arcs -ftest-coverage -o s21_helpers.o -c ../backend/s21_helpers.c && \
	ar rc s21_calc.a RPNeval.o InfixIntoRPN.o s21_helpers.o && \
	ranlib s21_calc.a && \
	gcc $(FLAGS) $(ASAN) -fprofile-arcs -ftest-coverage s21_test.c -o mytests -lcheck -L. s21_calc.a && \
	./mytests && \
	geninfo . -b . -o coverage.info && \
	genhtml coverage.info -o coverage 

gcov_report:
	open ./back_tests/coverage/index.html

leaks:
	leaks -atExit -- ./back_tests/mytests