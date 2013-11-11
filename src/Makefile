#--------------------------------------------------------
# File: Makefile    Author(s): Simon DÉSAULNIERS
#                              Frédéric Hamelin
# Date: 2013-11-11
#--------------------------------------------------------
# Makefile pour le projet inf1018 - tp2 
#--------------------------------------------------------

DEBUG=-g

all: analyseur.o syntaxique.o lexical.o
	gcc -o inf1018tp2 analyseur.o syntaxique.o lexical.o
analyseur.o: analyseur.c
	gcc $(DEBUG) -c analyseur.c
syntaxique.o: syntaxique.c syntaxique.h
	gcc $(DEBUG) -c syntaxique.c
lexical.o: lexical.c lexical.h
	gcc $(DEBUG) -c lexical.c
