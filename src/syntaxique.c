//-------------------------------------------------------
// File: syntaxique.c    Author(s): Simon Désaulniers
//                                  Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Gestion de la tâche syntaxique de l'analyseur.
//-------------------------------------------------------
#include "syntaxique.h"

proc *firstp = NULL; // la première procédure
proc *cur_proc = NULL; // la procédure en cours de construction

// token venant de l'analyseur lexical
char * token;

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
}

void analyse_syntax()
{
    // initialisation des variables nécessaires
    token = malloc(sizeof(char)*16);

    do {
        if (firstp == NULL) {
            //Initialisation de la liste de procédure
            firstp = malloc(sizeof(proc));
            *firstp = (proc){"", NULL, NULL};
            cur_proc = firstp;
        }
        else {
            cur_proc->next = malloc(sizeof(proc));
            cur_proc = cur_proc->next;
            *cur_proc = (proc){"", NULL, NULL};
        }
        procedure();
        peek_next(&token);
    }
    while (token != NULL);
}

void procedure()
{
    askForNext();
    printf("Analyse d'un bloc \'Procedure\', le token est:\n\'%s\'\n", token);

    if (strcmp(token, "Procedure") != 0)
    {
        fprintf(stderr, "%s : Le token attendu est \'Procedure\'\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }

    identificator(1,0);
    declarations();
    affectation_instructions();

    if (strcmp(token, "Fin_Procedure"))
    {
        fprintf(stderr, "%s : Le token attendu est \'Fin_Procedure\'\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }

    identificator(1, 0);
}

void declarations()
{
    declare *cur_decl;

    peek_next(&token); /*
                        * ne fait que regarder le next sans déplacer cur_pos 
                        */
    while (!strcmp(token, "declare")) {
        // la liste est vide
        if (!cur_proc->first_declare) {
            cur_decl = cur_proc->first_declare = cur_proc->last_declare = malloc(sizeof(declare));
        }
        else {
            cur_decl = cur_proc->last_declare->next = malloc(sizeof(declare));
            cur_proc->last_declare = cur_decl;
        }
        *cur_decl = (declare) {"", "", NULL};

        askForNext(); // prend le token declare en déplaçant cur_pos cette fois-ci
        declaration(cur_decl);
        peek_next(&token);
    }

    if (!cur_proc->first_declare) {
        fprintf(stderr, "%s : Au moins une (1) déclaration doit être faite.\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }
}

void declaration(declare *cur_decl)
{
    printf("Analyse d'une déclaration...\n");

    // on vérifie l'identifiant
    identificator(0, 0);
    // stockage du nom de variable
    strcpy(cur_decl->var, token);

    // récupération du token
    askForNext();
    if (*token != ':') {
        fprintf(stderr, "%s : Le token attendu est \':\'\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }

    type();
    //stockage du type de variable
    strcpy(cur_decl->type, token);

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

int identificator(int is_proc_id, int maybe)
{
    // Récupération du prochain token
    askForNext();
    printf("Analyse d'un identificateur, le token est:\n\'%s\'\n", token);

    if (strlen(token) > BIGGEST_ID_LENGTH) {
        if (maybe) {
            return 1;
        }
        fprintf(stderr, "%s : Un identificateur doit contenir maximum %i caractères.\n", SYNTAX_ERROR, BIGGEST_ID_LENGTH);
        exit(EXIT_FAILURE);
    }
    if (is_reserved(token)) {
        fprintf(stderr, "Un identificateur doit être différent des mots réservés du langage.\n");
        exit(EXIT_FAILURE);
    }

    // on a un id de procedure..
    if (is_proc_id) {
        // debut d'une procedure (Procedure <id>)
        if (!strcmp(cur_proc->id, "")) {
            strcpy(cur_proc->id, token);
        }
        // fin de procedure (Fin_procedure <id>)
        else if (strcmp(token, cur_proc->id)) {
            if (maybe) {
                return 1;
            }
            fprintf(stderr, "%s : L'identifcateur suivant le terminal \"Procedure\" doit coincider avec celui \
                    suivant le terminal \"Fin_Procedure\"\n", SYNTAX_ERROR);
            exit(EXIT_FAILURE);
        }
    }
    char *tok = token;

    // Vérification du caracètre commençant le token
    if (*tok < 65 || (*tok > 90 && *tok < 97) || *tok > 122) {
        if (maybe) {
            return 1;
        }
        fprintf(stderr, "%s : Le premier caractère d'un identificateur doit être une lettre.\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }
    
    while (*tok != '\0') {
        if (*tok < 48 || (*tok > 57 && *tok < 65) || (*tok > 90 && *tok < 97) || *tok > 122) {
            if (maybe) {
                return 1;
            }
            fprintf(stderr, "%s : Un identificateur doit contenir seulement des lettres et des chiffres.\n", SYNTAX_ERROR);
            exit(EXIT_FAILURE);
        }
        tok++;
    }
    return 0;
}

void affectation_instructions()
{
    do {
        affectation_instruction();
    }
    while (*token == ';');
}

void affectation_instruction()
{
    declare *affecting_var_decl;
    printf("Analyse d'une instruction d'affectation...\n");

    identificator(0, 0);
    affecting_var_decl = find_decl(token);
    if (!affecting_var_decl) {
        fprintf(stderr, "%s : La variable doit être préalablement déclarée\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }

    askForNext();
    if (*token != '=') {
        fprintf(stderr, "%s : Le token attendu est \'=\'\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }

    arithmetic_expression(affecting_var_decl->type);
}

void arithmetic_expression(char *affecting_type)
{
    printf("Analyse d'une expression arithmétique\n");
    do {
        term(affecting_type);
    } while (*token == '+' || *token == '-');
}

void term(char *affecting_type)
{
    printf("Analyse d'un terme...\n");

    do {
        factor(affecting_type);
        askForNext();
    } while (*token == '*' || *token == '/');
}

void factor(char *affecting_type)
{
    printf("Analyse d'un facteur...\n");

    if (!identificator(0, 1)) {
        declare *this_var_decl = find_decl(token);

        if (!this_var_decl) {
            fprintf(stderr, "%s : La variable doit être préalablement déclarée\n", SYNTAX_ERROR);
            exit(EXIT_FAILURE);
        }
        if (strcmp(affecting_type, "entier") && !strcmp(this_var_decl->type, affecting_type)) {
            fprintf(stderr, "%s : Une variable entière ne peut se faire attribuer un résultat réel.\n", SYNTAX_ERROR);
            exit(EXIT_FAILURE);
        }
        return;
    }

    rewind_pos(token);
    if (!number(1)) {
        return;
    }

    if (*token != '(') {
       fprintf(stderr, "%s : Le token attendu est un nombre, une variable ou \'(\'\n", SYNTAX_ERROR);
       exit(EXIT_FAILURE);
    }

    arithmetic_expression(affecting_type);

    if (*token != ')') { 
       fprintf(stderr, "%s : Le token attendu est \')\'\n", SYNTAX_ERROR);
       exit(EXIT_FAILURE);
    }
}

int number(int maybe)
{
    float f;

    askForNext();

    printf("Analyse d'un nombre, le token est :\n%s\n", token);
    if (sscanf(token, "%f", &f) == 0){
        if (maybe) {
            return 1;
        }
        fprintf(stderr, "%s : Le token attendu doit être un nombre.\n", SYNTAX_ERROR);
        exit(EXIT_FAILURE);
    }
    return 0;
}

declare* find_decl(char *var)
{
    declare* cur, *first;
    cur = first = cur_proc->first_declare;

    if (!first) {
        return NULL;
    }
    
    while (cur) {
        if (!strcmp(cur->var, var)) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}
