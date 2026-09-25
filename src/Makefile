CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror 

s21_string: s21_string.o
	$(CC) $(CFLAGS) s21_string.o -o s21_string

s21_string.o: s21_string.c s21_string.h
	$(CC) $(CFLAGS) -c s21_string.c -o s21_string.o

clean:
	rm -f *.o ./s21_string