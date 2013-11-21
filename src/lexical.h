//-------------------------------------------------------
// File: lexical.h    Author(s): Simon Désaulniers
//                               Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Fichier d'entête de lexical.c
//-------------------------------------------------------
#ifndef LEXICAL_4UGTM7YE

#define LEXICAL_4UGTM7YE


#include <analyseur.h>

char *cur_pos;
const char *INIT_POS;
const char all_delims[11], delims_n_token[8];


//----------------------------------------
// next()
// valeur de retour:
//  0: succès
//  -1: plus aucun caractère à traiter.
//  x (>0): espace nécessaire pour stocker
//      le token.
// Renvoie le prochain caractère à 
// traiter.
//----------------------------------------
int next(char**);

int in(const char[], char);

#endif /* end of include guard: LEXICAL_4UGTM7YE */

