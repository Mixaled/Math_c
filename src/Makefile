GCC= gcc -Wall -Wextra
GCOV_FLAGS= -fprofile-arcs -ftest-coverage

UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LINK_FLAGS=-lcheck -lsubunit -lrt -lm -lpthread
	LEAK=CK_FORK=no valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file="leak.log"
	SYSFLAG=-D LINUX
endif
ifeq ($(UNAME),Darwin)
	LINK_FLAGS=-lcheck -lm
	LEAK=CK_FORK=no leaks -quiet -atExit --
	SYSFLAG=-D APPLE
endif


all: s21_math.a

s21_math.a: s21_math.c s21_math.h
	$(GCC) $(SYSFLAG) -c s21_math.c
	ar rc s21_math.a *.o
	ranlib s21_math.a
	rm -f *.o

clean:
	rm -rf *.a
	rm -rf *.o
	rm -f test
	rm -f test_exec
	rm -f test_gcov
	rm -f *.gcda
	rm -f *.gcno
	rm -f test.log
	rm -f test.info
	rm -rf report/
	rm -f .clang-format
	rm -f gen
	rm -f test.c

test: test.log scripts/get_fails_for_funcs.sh
	bash scripts/get_fails_for_funcs.sh

test_gcov: test.c s21_math.c s21_math.h
	$(GCC) $(GCOV_FLAGS) $(SYSFLAG) s21_math.c test.c -L. $(LINK_FLAGS) -o test_gcov

gcov_report: test_gcov scripts/get_fails_for_funcs.sh
	(./test_gcov > test.log) || true
	bash scripts/get_fails_for_funcs.sh
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

get_failed_functions: test.log
	grep ":\w*[0-9]*:.: Assertion" test.log -o | grep "s21_\w*_test" -o | sort | uniq

test.log: test_exec
	(./test_exec > test.log) || true

style:
	clang-format -n -style=Google *.c *.h

style_force:
	clang-format -style=Google -dump-config > .clang-format
	clang-format -i *.c *.h

gen: gen_test.c test_data.h
	$(GCC) $(SYSFLAG) gen_test.c -o gen $(LINK_FLAGS)

test.c: gen
	./gen > test.c
	clang-format -style=Google -dump-config > .clang-format
	clang-format -i test.c

test_exec: s21_math.a test.c
	$(GCC) $(SYSFLAG) test.c s21_math.a -L. $(LINK_FLAGS) -o test_exec
