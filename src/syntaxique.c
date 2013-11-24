//-------------------------------------------------------
// File: syntaxique.c    Author(s): Simon Désaulniers
//                                  Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Gestion de la tâche syntaxique de l'analyseur.
//-------------------------------------------------------
#include "syntaxique.h"

char * token;
declared_var * vars;
int vars_count = 0;

int askForNext()
{
    int size = next(&token);
    
    if (size > 0) {
        token = malloc(sizeof(char) * (size+1));
        askForNext();
    }
    else if (size == -1) {
        fprintf(stderr, "Erreur : Fin du fichier inattendue.\n");
        exit(EXIT_FAILURE);
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

    identificator(1,NULL);

    declarations();

    affectation_instructions();


    if (strcmp(token, "Fin_Procedure") != 0)
    {
        fprintf(stderr, "Erreur : Le token attendu est : Fin_Procedure\n");
        return -1;
    }

    askForNext();

    identificator(1,NULL);

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
    
    if (!identificator(1,NULL)) {
        vars_count++;
        vars = (declared_var*)realloc(vars, vars_count * sizeof(declared_var));
        declared_var temp_var;
        strcpy(temp_var.name,token);
        strcpy(temp_var.type,token);
        vars[vars_count - 1] = temp_var;
    }

    askForNext();

    if (*token != ':') {
        fprintf(stderr, "Erreur : Le token attendu est : :\n");
        
        return -1;
    }

    if (!type()) {
        strcpy(vars[vars_count - 1].type, token);
    }

    askForNext();

    if (*token != ';') {
        fprintf(stderr, "Erreur : Le token attendu est : ;\n");
        
        return -1;
    }

    return 0;
}


int type()
{
    askForNext();

    if (strcmp(token, "entier") != 0 && strcmp(token, "réel") != 0) {
        fprintf(stderr, "Erreur : Le type doit être : entier ou réel\n");
        
        return -1;
    }
}

int identificator(int message, declared_var * match)
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

    if (match != NULL) {
        int i;
        for (i = 0; i < vars_count;i++) {
            if (!strcmp(vars[i].name,token)) {
                *match = vars[i];
                break;
            }
        }
    }

    return 0;
}

int affectation_instructions()
{

    do {
        if (*token == ';')
            askForNext();
        affectation_instruction();
    } while (*token == ';');
    return 0;
}

int affectation_instruction()
{
    declared_var receiving_var;
    strcpy(receiving_var.name, "");
    strcpy(receiving_var.type, "");
    identificator(1, &receiving_var);

    askForNext();

    if (*token != '=') {
        fprintf(stderr, "Erreur : Le token attendu est : =\n");
       
        return -1;
    }
    int isInteger = 1;

    arithmetic_expression(&isInteger);

    if (!isInteger && !strcmp(receiving_var.type, "entier")) {
        fprintf(stderr,"Erreur : Impossible d'assigner un réel à une variable de type entier.\n");
    }
    return 0;
}

int arithmetic_expression(int * isInteger)
{
    do
    {
        term(isInteger);
        if (*token != '+' && *token != '-' && *token != ';' && strcmp(token,"Fin_Procedure") != 0 && *token != ')')
            askForNext();
    } while (*token == '+' || *token == '-');

    return 0;
}

int term(int * isInteger)
{
    do 
    {
        factor(isInteger);
        if (*token != '*' && *token != '/' && *token != '+' && *token != '-' && *token != ';' && strcmp(token,"Fin_Procedure") != 0 && *token != ')')
            askForNext();
    } while (*token == '*' || *token == '/');

    return 0;
}

int factor(int* isInteger)
{
   askForNext();
   declared_var factor_var;
   if (!identificator(0,&factor_var)) {
        if (!strcmp(factor_var.name, "")) {
            fprintf(stderr, "Erreur : La variable %s n'est pas déclarée.\n", token);
            return -1;
        }
        
        if (*isInteger && !strcmp(factor_var.name, "réel")) {
            *isInteger = 0;
        }
        return 0;
   }

   if (!number(0,isInteger)) {
        return 0;
   }

   if (*token != '(') {
       fprintf(stderr, "Erreur : Le token attendu est un nombre, une variable ou (\n");
       
       return -1;
   }

   arithmetic_expression(isInteger);


   if (*token != ')') { 
       fprintf(stderr, "Erreur : Le token attendu est : )\n");

       return -1;
   }

   askForNext();
   return 0; 
}

int number(int message, int * isInteger)
{
    char* endptr;
    double value = strtod(token, &endptr);

    if (*endptr != 0){
        if (message)
            fprintf(stderr, "Erreur : Le token attendu doit être un nombre.\n");
        return -1;
    }
    if (atoi(token) != value && *isInteger) {
        *isInteger = 0;
    }
    return 0;
}
