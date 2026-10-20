CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror 
AR = ar 
ARFLAGS = rcs 

all: s21_string.a s21_string

s21_string.a: s21_string.o
	$(AR) $(ARFLAGS) $@ $^

s21_string.o: s21_string.c s21_string.h 
	$(CC) $(CFLAGS) -c s21_string.c -o s21_string.o

test.o: test.c s21_string.h
	$(CC) $(CFLAGS) $$(pkg-config --cflags check) -c test.c -o test.o

s21_string: test.o s21_string.a
	$(CC) $(CFLAGS) test.o s21_string.a $$(pkg-config --libs check) -o s21_string

test: s21_string
	./s21_string

clean:
	rm -f *.o *.a ./s21_string *.gcda *.gcno *.gcov *.html *.css *.exe

gcov_report:
	$(MAKE) clean
	$(MAKE) CFLAGS="-std=c11 -Wall -Wextra -Werror --coverage" test
	gcov s21_string.c
	gcovr -r . --html --html-details -o gcov_report.html


.PHONY: all test clean gcov_report