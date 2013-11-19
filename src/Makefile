#--------------------------------------------------------
# File: Makefile    Author(s): Simon DÉSAULNIERS
#                              Frédéric Hamelin
# Date: 2013-11-11
#--------------------------------------------------------
# Makefile pour le projet inf1018 - tp2 
#--------------------------------------------------------

BINDIR=../bin
DEBUG=-g

all: analyseur.o syntaxique.o lexical.o
	mkdir -p $(BINDIR)
	gcc -o $(BINDIR)/inf1018tp2 analyseur.o syntaxique.o lexical.o
analyseur.o: analyseur.c
	gcc -I. $(DEBUG) -c analyseur.c
syntaxique.o: syntaxique.c syntaxique.h
	gcc -I. $(DEBUG) -c syntaxique.c
lexical.o: lexical.c lexical.h
	gcc -I. $(DEBUG) -c lexical.c
clean:
	rm -rf *.o
