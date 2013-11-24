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

typedef struct declared_var {
    char name[9];
    char type[7];
} declared_var;

int procedure();
int declarations();
int declaration();
int affectation_instructions();
int affectation_instruction();
int type();
int identificator(int,declared_var*);
int arithmetic_expression(int*);
int term(int*);
int factor(int*);
int number(int,int*);

#endif
