//-------------------------------------------------------
// File: syntaxique.c    Author(s): Simon Désaulniers
//                                  Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Gestion de la tâche syntaxique de l'analyseur.
//-------------------------------------------------------
#include "syntaxique.h"

char * token;

int askForNext()
{
    int size = next(&token);
    
    if (size > 0) {
        token = malloc(sizeof(char) * (size+1));
        askForNext();
    }
    else if (size == -1) {
        fprintf(stdout, "Analyse lexicale et syntaxique terminée.\n");
        exit(EXIT_SUCCESS);
    }
    else if (!size)
        printf("Analyse du token : %s\n", token);
}

int procedure()
{
    token = malloc(sizeof(char) * 16);
    askForNext();

    if (strcmp(token, "Procedure") != 0)
    {
        fprintf(stderr, "Erreur : Le token attendu est : Procedure\n");
        return -1;
    }

    askForNext();

    identificator(1);

    declarations();

    affectation_instructions();


    if (strcmp(token, "Fin_Procedure") != 0)
    {
        askForNext();
        fprintf(stderr, "Erreur : Le token attendu est : Fin_Procedure\n");
        return -1;
    }

    askForNext();

    identificator(1);

    return 0;
}

int declarations()
{
    askForNext();

    while (strcmp(token, "declare") == 0) {
        declaration();
        askForNext();
    }

    

    return 0;
}

int declaration()
{
    askForNext();
    
    variable(1);

    askForNext();

    if (*token != ':') {
        fprintf(stderr, "Erreur : Le token attendu est : :\n");
        
        return -1;
    }

    type();

    askForNext();

    if (*token != ';') {
        fprintf(stderr, "Erreur : Le token attendu est : ;\n");
        
        return -1;
    }

    return 0;
}

int variable(int message)
{
    return identificator(message);
}

int type()
{
    askForNext();

    if (strcmp(token, "entier") != 0 && strcmp(token, "réel") != 0) {
        fprintf(stderr, "Erreur : Le type doit être : entier ou réel\n");
        
        return -1;
    }
}

int identificator(int message)
{
    if (strlen(token) > 8) {
        if (message)
            fprintf(stderr, "Erreur : Un identificateur doit contenir maximum 8 caractères.\n");
        
        return -1;
    }
    int position = 0;
    int ascii;

    ascii = (int)*token;

    if (ascii < 65 || (ascii > 90 && ascii < 97) || ascii > 122) {
        if (message)
            fprintf(stderr, "Erreur : Le premier caractère d'un identificateur doit être une lettre.\n");
        
        token -= position;
        return -1;
    }
    
    token++;
    position++;

    while (*token != '\0') {
        
        ascii =(int)*token;
        if (ascii < 48 || (ascii > 57 && ascii < 65) || (ascii > 90 && ascii < 97) || ascii > 122) {
            if (message)
                fprintf(stderr, "Erreur : Un identificateur doit contenir seulement des lettres et des chiffres.\n");
            
            token -= position;
            return -1;
        }

        token++;
        position++;
    }

    token -= position;
    return 0;
}

int affectation_instructions()
{

    do {
        affectation_instruction();
        if (*token != ';') 
            askForNext();
    } while (!*token == ';');

    return 0;
}

int affectation_instruction()
{

    variable(1);

    askForNext();

    if (*token != '=') {
        fprintf(stderr, "Erreur : Le token attendu est : =\n");
       
        return -1;
    }

    arithmetic_expression();

    return 0;
}

int arithmetic_expression()
{
    do
    {
        term();
        if (*token != '+' && *token != '-')
            askForNext();
    } while (!*token == '+' || !*token == '-');

    return 0;
}

int term()
{
    do 
    {
        factor();
        askForNext();
    } while (!*token != '*' || !*token != '/');

    return 0;
}

int factor()
{
   askForNext();

   if (!variable(0)) {
        return 0;
   }

   if (!number(0)) {
        return 0;
   }

   if (*token == '(') {
       fprintf(stderr, "Erreur : Le token attendu est un nombre, une variable ou (\n");
       
       return -1;
   }

   arithmetic_expression();

   askForNext();

   if (*token != ')') { 
       fprintf(stderr, "Erreur : Le token attendu est : )\n");

       return -1;
   }

   return 0; 
}

int number(int message)
{
    askForNext();
    
    float f;

    if (sscanf(token, "%f", &f) == 0){
        if (message)
            fprintf(stderr, "Erreur : Le token attendu doit être un nombre.\n");
        return -1;
    }
    return 0;
}
