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

    identificateur();

    declarations();

    instructions_affectation();

    token = next();

    if (strcmp(token, "Fin_Procedure") != 0)
    {
        //Erreur
        return 0;
    }

    identificateur();

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
    return identificateur();
}

int type()
{
    token = next();

    if (strcmp(token, "entier") != 0 && strcmp(token, "réel") != 0) {
        //erreur
        return 0;
    }
}

int identificateur()
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

int instructions_affectation()
{
    instruction_affectation();

    token = next();
    while (strcmp(token, ";") == 0) {
        instruction_affectation();

        token = next();
    }

    token = last();

    return 1;
}

int instruction_affectation()
{
    variable();

    token = next();

    if (strcmp(token, "=") != 0) {
        //erreur
        return 0;
    }

    expression_arithmetique();

    return 1;
}

int expression_arithmetique()
{
    terme();

    token = next();

    while (strcmp(token, "+") == 0 || strcmp(token, "-") == 0) {
        terme();
        token = next();
    }

    token = last();

    return 1;
}

int terme()
{
    facteur();

    token = next();
    while (strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
        facteur();
        token = next();
    }

    token = last();

    return 1;
}

int facteur()
{
   if (variable() == 1) {
        return 1;
   }

   token = last();

   if (nombre() == 1) {
        return 1;
   }

   if (strcmp(token, "(") != 0) {
       //erreur 
       return 0;
   }

   expression_arithmetique();

   token = next();

   if (strcmp(token, ")") != 0) {
       //erreur 
       return 0;
   }

   return 1; 
}

int nombre()
{
    token = next();
    
    float f;

    if (sscanf(token, "%f", &f) == 0){
        //erreur
        return 0;
    }
    return 1;
}
