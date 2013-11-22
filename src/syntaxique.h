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
    char var[8];
    char type[6];
    struct _declaration *next;
} declaration;

typedef struct _procedure {
    char *id;
    declaration *first_declare;
    struct _procedure *next;
} procedure;

void proceduref();
void declarations();
void declaration();
void affectation_instructions();
void affectation_instruction();
void variable();
void type();
int identificator(char **proc_id);
void arithmetic_expression();
void term();
void factor();
int number();

#endif
