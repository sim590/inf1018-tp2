//-------------------------------------------------------
// File: lexical.c    Author(s): Simon Désaulniers
//                               Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Gestion des tâches lexicales de l'analyseur
//-------------------------------------------------------
#include "lexical.h"

const char delims_n_token[] =  {'=', '+', '-', '*', '/', ':', ';', '(', ')', '\0'},
    all_delims[] =  {' ', '\n', '\t', '=', '+', '-', '*', '/', ':', ';', '(', ')', '\0'}; // On doit terminer le array par un \0 pour  

int next(char **token)
{
    
    // plus de token à analyser, mais
    // dépassemnet de l'espace mémoire réservé
    if (cur_pos > INIT_POS+BUFLEN-1) {
        *token = NULL+1;
        return -2;
    }

    char *tok = NULL;

    while (in(all_delims, MAIN_BUFFER[cur_pos-INIT_POS])) { //*((char*)((long)MAIN_BUFFER+(long)cur_pos-INIT_POS)) 

        cur_pos++;
        
        // si le token est un délimiteur
        if (in(delims_n_token, MAIN_BUFFER[cur_pos-INIT_POS-1])) {
            sprintf(*token, "%c\0", MAIN_BUFFER[cur_pos-INIT_POS-1]);
            return 0;
        }
    }

    // on récupère le token
    tok = strtok(cur_pos, all_delims);

    // plus de token à analyser
    if (!tok) {
        *token = NULL;
        return -1;
    }

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
