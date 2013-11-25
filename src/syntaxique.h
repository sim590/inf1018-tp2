//-------------------------------------------------------
// File: syntaxique.h    Author(s): Simon Désaulniers
//                                  Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Fichier d'entête de la gestion syntaxique de 
// l'analyseur
//-------------------------------------------------------
#ifndef SYNTAXIQUE_4WEDD4T

#define SYNTAXIQUE_4WEDD4T

#include <analyseur.h>
#include <lexical.h>

#define SYNTAX_ERROR "erreur de syntaxe"
#define BIGGEST_ID_LENGTH 8

typedef struct _declaration {
    char var[9];
    char type[7];
    struct _declaration *next;
} declare;

typedef struct _procedure {
    char id[9];
    declare *first_declare;
    declare *last_declare;
    struct _procedure *next;
} proc;

void procedure();
void declarations();
void declaration(declare*);
void affectation_instructions();
void affectation_instruction();
void variable();
void type();
int identificator(int, int);
void arithmetic_expression();
void term();
void factor();
int number(int);

declare* find_decl(char*);

#endif
