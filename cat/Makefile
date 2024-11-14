CC = gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11

CF_CHECK = clang-format  -n
CF_APPLY = clang-format  -i
RM = rm -rf 


all :  s21_cat

format : 
	$(CF_CHECK) *.c
	$(CF_CHECK) *.h
	$(CF_APPLY) *.c
	$(CF_APPLY) *.h
	
s21_cat : s21_cat.o lib.o
	$(CC) s21_cat.o lib.o -o s21_cat

s21_cat.o : s21_cat.c
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat.o
lib.o : lib.c
	$(CC) $(CFLAGS) lib.c -o lib.o
clean :
	$(RM) *.o *.a *.so

rebuild : clean s21_cat
