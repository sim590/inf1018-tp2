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
int instructions_affectation();
int instruction_affectation();
int variable();
int type();
int identificateur();
int expression_arithmetique();
int terme();
int facteur();
int nombre();

#endif
