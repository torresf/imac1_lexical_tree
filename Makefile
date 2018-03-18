CFLAGS = -Wall -ansi

Lexique: Lexique.o arbre.o
	gcc -o Lexique arbre.o Lexique.o 

Lexique.o: Lexique.c arbre.h
	gcc -o Lexique.o -c Lexique.c $(CFLAGS)

arbre.o: arbre.c
	gcc -o arbre.o -c $< $(CFLAGS)