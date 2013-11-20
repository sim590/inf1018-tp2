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

const char delims[], delims_n_token[];

//----------------------------------------
// next()
// valeur de retour:
//  0: succès
//  -1: plus aucun caractère à traiter.
//  TOKEN_TOO_SMALL: pas assez d'espace pour
//      stocker le token.
// Renvoie le prochain caractère à 
// traiter.
//----------------------------------------
int next(char**);

#endif /* end of include guard: LEXICAL_4UGTM7YE */

