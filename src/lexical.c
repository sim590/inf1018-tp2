//-------------------------------------------------------
// File: lexical.c    Author(s): Simon Désaulniers
//                               Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Gestion des tâches lexicales de l'analyseur
//-------------------------------------------------------
#include "lexical.h"

delims_n_token =  {'+', '-', '*', '/', ':', ';', '(', ')'};
all_delims =  {' ', '\n', '\t','+', '-', '*', '/', ':', ';', '(', ')'};

int next(char **token)
{
    static char *cur_pos = strdup(MAIN_BUFFER),/*
                                                * Première initialisation
                                                * (qu'une seule fois), i.e aux
                                                * autres appels de next(),
                                                * l'initialisation ne se fera
                                                * pas et donc on gardera un
                                                * suivi sur la valeur de la
                                                * position (c'est dû au
                                                * terminal "static").
                                                */
                *tok = NULL;
    //pointeur initial
    static const char *INIT_POS = cur_pos;

    while (in(all_delims, *(MAIN_BUFFER+cur_pos-INIT_POS))) {
        cur_pos++;
        
        // si le token est un délimiteur
        if (in(delims_n_token, *(MAIN_BUFFER+cur_pos-INIT_POS-1))) {
            sprintf(*token, "%c\0", *(MAIN_BUFFER+cur_pos-INIT_POS-1));
            return 0;
        }
    }

    // dépassemnet de l'espace mémoire réservé
    if (cur_pos >= INIT_POS+BUFLEN-1) {
        *token = NULL;
        return -1;
    }

    // on récupère le token
    tok = strtok(cur_pos, all_delims);

    int toksize = strlen(tok);
    if (toksize > malloc_usable_size(*token)) {
        *token = NULL;
        
        // retourne le nombre de caractères nécessaires.
        return toksize;
    }

    cur_pos += toksize;
    strcpy(*token, tok);
    return 0;
}

bool in(char delims[], char token)
{
    for (i = 0; i < strlen(delims); i++) {
        if (token == delims[i]) {
            return true;
        }
    }
    return false;
}
