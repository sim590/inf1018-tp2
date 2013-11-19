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

int lastTokenSize;
//------------
//Fonctions 
//------------

//----------------------------------------
// next()
// valeur de retour:
//  char*: le prochain token à analyser.
//----------------------------------------
char * next();

//----------------------------------------
// last()
// valeur de retour:
//  char*: le token précédent.
//----------------------------------------
char * last();

//----------------------
// getLastCharacters()
// valeur de retour:
//  char*: ?
// description?
//----------------------
char * getLastCharacters(int strLength);

#endif /* end of include guard: LEXICAL_4UGTM7YE */

