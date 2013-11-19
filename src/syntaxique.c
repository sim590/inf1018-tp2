//-------------------------------------------------------
// File: syntaxique.c    Author(s): Simon Désaulniers
//                                  Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Gestion de la tâche syntaxique de l'analyseur.
//-------------------------------------------------------
#include "syntaxique.h"

char * token;

int procedure()
{
    token = next();

    if (strcmp(token, "Procedure") != 0)
    {
        //Erreur
        return 0;
    }

    identificator();

    declarations();

    affectation_instructions();

    token = next();

    if (strcmp(token, "Fin_Procedure") != 0)
    {
        //Erreur
        return 0;
    }

    identificator();

    return 1;
}

int declarations()
{
    token = next();

    while (strcmp(token, "declare") == 0) {
        declaration();
    }

    token = last();

    return 1;
}

int declaration()
{
    variable();

    token = next();

    if (strcmp(token, ":") != 0) {
        //erreur
        return 0;
    }

    type();

    if (strcmp(token, ";") != 0) {
        //erreur
        return 0;
    }

    return 1;
}

int variable()
{
    return identificator();
}

int type()
{
    token = next();

    if (strcmp(token, "entier") != 0 && strcmp(token, "réel") != 0) {
        //erreur
        return 0;
    }
}

int identificator()
{
    token = next();

    if (sizeof(*token) > 8) {
        //erreur
        return 0;
    }

    int ascii;

    ascii = (int)*token;

    if (ascii < 65 || (ascii > 90 && ascii < 97) || ascii > 122) {
        //erreur
        return 0;
    }
    
    token++;

    while (*token != '\0') {
        
        ascii =(int)*token;
        if (ascii < 48 || (ascii > 57 && ascii < 65) || (ascii > 90 && ascii < 97) || ascii > 122) {
            //erreur
            return 0;
        }

        token++;
    }

    return 1;
}

int affectation_instructions()
{
    affectation_instruction();

    token = next();
    while (strcmp(token, ";") == 0) {
        affectation_instruction();

        token = next();
    }

    token = last();

    return 1;
}

int affectation_instruction()
{
    variable();

    token = next();

    if (strcmp(token, "=") != 0) {
        //erreur
        return 0;
    }

    arithmetic_expression();

    return 1;
}

int arithmetic_expression()
{
    term();

    token = next();

    while (strcmp(token, "+") == 0 || strcmp(token, "-") == 0) {
        term();
        token = next();
    }

    token = last();

    return 1;
}

int term()
{
    factor();

    token = next();
    while (strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
        factor();
        token = next();
    }

    token = last();

    return 1;
}

int factor()
{
   if (variable() == 1) {
        return 1;
   }

   token = last();

   if (number() == 1) {
        return 1;
   }

   if (strcmp(token, "(") != 0) {
       //erreur 
       return 0;
   }

   arithmetic_expression();

   token = next();

   if (strcmp(token, ")") != 0) {
       //erreur 
       return 0;
   }

   return 1; 
}

int number()
{
    token = next();
    
    float f;

    if (sscanf(token, "%f", &f) == 0){
        //erreur
        return 0;
    }
    return 1;
}
