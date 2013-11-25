//-------------------------------------------------------
// File: lexical.c    Author(s): Simon Désaulniers
//                               Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Gestion des tâches lexicales de l'analyseur
//-------------------------------------------------------
#include "lexical.h"

static const lexicons lexicon = {
    /*lexicon.all_delims*/ {' ', '\n', '\t', '=', '+', '-', '*', '/', ':', ';', '(', ')', '\0'},
    /*lexicon.delims_n_tokenss*/ {'=', '+', '-', '*', '/', ':', ';', '(', ')', '\0'},
    /*reserved_words*/ {"Procedure\0", "Fin_Procedure\0", "declare\0", "entier\0", "réel\0"}
};


int next(char **token)
{
    
    // plus de token à analyser, mais
    // dépassemnet de l'espace mémoire réservé
    if (cur_pos > INIT_POS+BUFLEN-1) {
        *token = NULL+1;
        return -2;
    }

    char *tok = NULL;

    while (in(lexicon.all_delims, MAIN_BUFFER[cur_pos-INIT_POS])) {

        cur_pos++;
        
        // si le token est un délimiteur
        if (in(lexicon.delims_n_tokens, MAIN_BUFFER[cur_pos-INIT_POS-1])) {
            sprintf(*token, "%c\0", MAIN_BUFFER[cur_pos-INIT_POS-1]);
            return 0;
        }
    }

    // on récupère le token
    tok = strtok(cur_pos, lexicon.all_delims);

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

void peek_next(char **token)
{
    char *tok = *token;
    next(token);
    rewind_pos(tok);
}

void rewind_pos(char *token)
{
    cur_pos[0] = MAIN_BUFFER[cur_pos-INIT_POS];
    cur_pos-=strlen(token)+1;
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

int is_reserved(char *token)
{
    int i;
    for (i = 0; i < NUMBER_RESERVED_WORDS; i++) {
        if (!strcmp(lexicon.reserved_words[i], token)) {
            return 1;
        }
    }
    return 0;
}
