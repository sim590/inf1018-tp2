//-------------------------------------------------------
// File: lexical.h    Author(s): Simon Désaulniers
//                               Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Fichier d'entête de lexical.c
//-------------------------------------------------------
#ifndef LEXICAL_4UGTM7YE

#define LEXICAL_4UGTM7YE

#include <stdio.h>
#include <stdlib.h>

//Variables
char *buffer;
int lastTokenSize;
//------------
//Fonctions 
//------------

//----------------------------
// loadFile()
// valeur de retour:
//  void
// load le fichier et le met
// dans le buffer
//----------------------------
void loadFile(char *filename);

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

