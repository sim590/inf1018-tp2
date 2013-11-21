//-------------------------------------------------------
// File: lexical.c    Author(s): Simon Désaulniers
//                               Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Gestion des tâches lexicales de l'analyseur
//-------------------------------------------------------
#include "lexical.h"

const char delims_n_token[] =  {'+', '-', '*', '/', ':', ';', '(', ')'},
    all_delims[] =  {' ', '\0',  '\n', '\t','+', '-', '*', '/', ':', ';', '(', ')'};

int next(char **token)
{
    
    char *tok = NULL;

    //pointeur initial
    while (in(all_delims, *((char*)((long)MAIN_BUFFER+(long)cur_pos-(long)INIT_POS)))) {

        cur_pos++;
        
        // si le token est un délimiteur
        if (in(delims_n_token, *((char*)((long)MAIN_BUFFER+(long)cur_pos-(long)INIT_POS-1)))) {
            sprintf(*token, "%c\0", *((char*)((long)MAIN_BUFFER+(long)cur_pos-(long)INIT_POS-1)));
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

int in(const char delims[], char token)
{
    int i;
    for (i = 0; i < strlen(delims); i++) {
        if (token == delims[i]) {
            return 1;
        }
    }
    return 0;
}
