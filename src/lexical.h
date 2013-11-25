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

#define NUMBER_RESERVED_WORDS 5

char *cur_pos, *INIT_POS;

typedef struct _lexicon {
    char all_delims[13];
    char delims_n_tokens[10];
    char reserved_words[NUMBER_RESERVED_WORDS][16];
} lexicons;

//----------------------------------------
// next()
// valeur de retour:
//  0: succès
//  -1: plus aucun caractère à traiter.
//  -2: dépassement de l'espace tampon.
//  x (>0): espace nécessaire pour stocker
//      le token.
// Renvoie le prochain caractère à 
// traiter.
//----------------------------------------
int next(char**);
void peek_next(char**);
void rewind_pos(char *);
int is_reserved(char *);
int in(const char[], char);

#endif /* end of include guard: LEXICAL_4UGTM7YE */

