//-------------------------------------------------------
// File: syntaxique.c    Author(s): Simon Désaulniers
//                                  Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Gestion de la tâche syntaxique de l'analyseur.
//-------------------------------------------------------
#include "syntaxique.h"

// token venant de l'analyseur lexical
char * token;

// la première procédure
procedure *firstp = NULL;

void askForNext()
{
    int size = next(&token);
    
    if (size > 0) {
        token = malloc(sizeof(char) * (size+1));
        askForNext();
    }
    else if (size < 0) {
        fprintf(stderr, "%s : Fin du fichier inattendue.\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }
    else if (!size)
        printf("Analyse du token : %s\n", token);
}

void analyse_syntax()
{
    // initialisation des variables nécessaires
    token = malloc(sizeof(char)*16);
    err_msg = malloc(sizeof(char)*128);
    procedure cur_proc;

    while (cur_pos < INIT_POS + BUFLEN) {
        if (firstp == NULL) {
            //Initialisation de la liste de procédure
            firstp = malloc(sizeof(procedure));
            *firstp = (procedure){"", NULL, NULL};
            cur_proc = firstp;
        }
        else {
            cur_proc->next = malloc(sizeof(procedure));
            cur_proc = cur_proc->next;
            *cur_proc = (procedure){"", NULL, NULL};
        }
        proceduref(cur_proc);
    }
}

void proceduref(procedure *cur_proc)
{
    askForNext();

    if (strcmp(token, "Procedure") != 0)
    {
        fprintf(stderr, "%s : Le token attendu est \'Procedure\'\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }

    identificator(&cur_proc->id);

    declarations();

    affectation_instructions();


    if (strcmp(token, "Fin_Procedure") != 0)
    {
        fprintf(stderr, "%s : Le token attendu est \'Fin_Procedure\'\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }

    askForNext();

    identificator(NULL);
}

void declarations()
{
    do
    {
        declaration();
        askForNext();
    }
    while (strcmp(token, "declare") == 0)
}

void declaration()
{
    // on vérifie l'identifiant
    identificator(NULL);

    // récupération du token
    askForNext();
    if (*token != ':') {
        fprintf(stderr, "%s : Le token attendu est \':\'\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }

    type();

    askForNext();
    if (*token != ';') {
        fprintf(stderr, "%s : Le token attendu est \';\'\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }
}


void type()
{
    askForNext();
    if (strcmp(token, "entier") && strcmp(token, "réel")) {
        fprintf(stderr, "%s : Le type doit être \'entier\' ou \'réel\'\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }
}

int identificator(char **proc_id)
{
    if (strlen(token) > BIGGEST_ID_LENGTH) {
        fprintf(stderr, "%s : Un identificateur doit contenir maximum %s caractères.\n", SYNTAX_ERROR, BIGGEST_ID_LENGTH);
        exit(EXIT_FAILURE);
    }

    // Récupération du prochain token
    askForNext();
    if (proc_id != NULL && strcmp(token, *proc_id)) {
        fprintf(stderr, "%s : L'identifcateur suivant le terminal \"Procedure\" doit coincider avec celui \
                suivant le terminal \"Fin_Procedure\"\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }
    char *tok = token;

    // Vérification du caracètre commençant le token
    if (*tok < 65 || (*tok > 90 && *tok < 97) || *tok > 122) {
        fprintf(stderr, "%s : Le premier caractère d'un identificateur doit être une lettre.\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }
    
    while (*tok != '\0') {
        tok++
        if (*tok < 48 || (*tok > 57 && *tok < 65) || (*tok > 90 && *tok < 97) || *tok > 122) {
            fprintf(stderr, "%s : Un identificateur doit contenir seulement des lettres et des chiffres.\n", SYNTAX_ERROR);
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}

void affectation_instructions()
{
    do {
        affectation_instruction();
    } while (*token == ';');
}

void affectation_instruction()
{

    identificator();

    askForNext();

    if (*token != '=') {
        fprintf(stderr, "%s : Le token attendu est : =\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }

    arithmetic_expression();
}

void arithmetic_expression()
{
    do
    {
        term();
        if (*token != '+' && *token != '-' && *token != ';' && strcmp(token,"Fin_Procedure") != 0 && *token != ')')
            askForNext();
    } while (*token == '+' || *token == '-');
}

void term()
{
    do 
    {
        factor();
        if (*token != '*' && *token != '/' && *token != '+' && *token != '-' && *token != ';' && strcmp(token,"Fin_Procedure") != 0 && *token != ')')
            askForNext();
    } while (*token == '*' || *token == '/');
}

void factor()
{
   askForNext();

   if (!identificator(NULL)) {
        return;
   }

   if (!number()) {
        return;
   }

   if (*token != '(') {
       fprintf(stderr, "%s : Le token attendu est un nombre, une variable ou \'(\'\n", SYNTAX_ERROR);
       exit(EXIT_FAILURE);
   }

   arithmetic_expression();


   if (*token != ')') { 
       fprintf(stderr, "%s : Le token attendu est : )\n", SYNTAX_ERROR);

       exit(EXIT_FAILURE);
   }

   askForNext();
}

int number()
{
    
    float f;

    if (sscanf(token, "%f", &f) == 0){
        if (message)
            fprintf(stderr, "%s : Le token attendu doit être un nombre.\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }
    return 0;
}
