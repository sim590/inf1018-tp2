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
#include "lexical.h"

int procedure();
int declarations();
int declaration();
int affectation_instructions();
int affectation_instruction();
int variable();
int type();
int identificator();
int arithmetic_expression();
int term();
int factor();
int number();

#endif
