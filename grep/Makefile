CC = gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11

CF_CHECK = clang-format  -n
CF_APPLY = clang-format  -i
RM = rm -rf 


all :  s21_grep

format : 
	$(CF_CHECK) *.c
	$(CF_CHECK) *.h
	$(CF_APPLY) *.c
	$(CF_APPLY) *.h
	
s21_grep : s21_grep.o lib.o
	$(CC) s21_grep.o lib.o -o s21_grep

s21_grep.o : s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep.o
lib.o : lib.c
	$(CC) $(CFLAGS) lib.c -o lib.o
clean :
	$(RM) *.o *.a *.so

rebuild : clean s21_grep
