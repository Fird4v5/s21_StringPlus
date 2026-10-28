CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror 
AR = ar 
ARFLAGS = rcs 
GCOV_FLAGS = --coverage 
COVERAGE_FILE = coverage.info
COVERAGE_DIR = coverage_report 

all: s21_string.a

s21_string.a: s21_string.o
	$(AR) $(ARFLAGS) $@ $^

s21_string.o: s21_string.c s21_string.h
	$(CC) $(CFLAGS) -c $< -o $@

test.o: test.c s21_string.h
	$(CC) $(CFLAGS) $(shell pkg-config --cflags check) -c $< -o $@

test_runner: test.o s21_string.a
	$(CC) $(CFLAGS) $^ $(shell pkg-config --libs check) -o $@

test: test_runner
	./test_runner

gcov_report: 
	$(MAKE) clean
	$(MAKE) CFLAGS="$(CFLAGS) $(GCOV_FLAGS)" test
	lcov --capture --directory . --output-file $(COVERAGE_FILE)
	lcov --remove $(COVERAGE_FILE) '*/test.c' --output-file $(COVERAGE_FILE)
	genhtml $(COVERAGE_FILE) --output-directory $(COVERAGE_DIR) 


clean:
	rm -f *.o *.a test_runner *.gcda *.gcno *.gcov $(COVERAGE_FILE)
	rm -rf $(COVERAGE_DIR)

.PHONY: all test clean gcov_report
