#include "syntaxique.h"

char * token;

void procedure()
{
    token = next();

    if (strcmp(token, "Procedure") != 0)
    {
        //Erreur
        return;
    }

    identificateur();

    declarations();

    instructions_affectation();

    token = next();

    if (strcmp(token, "Fin_Procedure") != 0)
    {
        //Erreur
        return;
    }

    identificateur();

}

void declarations()
{
    token = next();

    while (strcmp(token, "declare") == 0) {
        declaration();
    }
}

void declaration()
{
    variable();

    token = next();

    if (strcmp(token, ":") != 0) {
        //erreur
        return;
    }

    type();

    if (strcmp(token, ";") != 0) {
        //erreur
        return;
    }
}

void variable()
{
    identificateur();
}

void type()
{
    token = next();

    if (strcmp(token, "entier") != 0 && strcmp(token, "réel") != 0) {
        //erreur
        return;
    }
}

void identificateur()
{
    token = next();

    if (sizeof(*token) > 8) {
        //erreur
        return;
    }

    int ascii;

    ascii = (int)*token;

    if (ascii < 65 || (ascii > 90 && ascii < 97) || ascii > 122) {
        //erreur
        return;
    }
    
    token++;

    while (*token != '\0') {
        
        ascii =(int)*token;
        if (ascii < 48 || (ascii > 57 && ascii < 65) || (ascii > 90 && ascii < 97) || ascii > 122) {
            //erreur
            return;
        }

        token++;
    }

}
