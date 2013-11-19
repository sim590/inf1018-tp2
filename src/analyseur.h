//-------------------------------------------------------
// File: analyseur.h    Author(s): Simon Désaulniers
//                                 Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Fichier d'entête de analyseur.c
//-------------------------------------------------------
#ifndef ANALYSEUR_4BB0V0UD

#define ANALYSEUR_4BB0V0UD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define LEXEMS_FILENAME "./lexems"
#define MISSING_ARG "Arguemnt manquant."
#define HELP "inf1018tp2 -- analyseur lexical et syntaxique\n\
SYNPOSYS : inf1018tp2 [OPTIONS] file\n\
\tfile\n\
\t\tLe fichier duquel tirer le texte à anlayser.\n\
OPTIONS\n\
\t-l|--lexems lexems_filename\
\t\tIndique le fichier dans lequel prendre le lexique (par défaut: ./lexems)\n\
\t-h|--help\n\
\t\tAffiche un texte d\'aide\n"

//Variables
char *buffer, *input_filename, *lexems, *lexems_filename;

//-----------
//Fonctions
//-----------


//----------------------------
// loadFile()
// valeur de retour:
//  void
// charge le fichier et
// le place dans un tampon.
//----------------------------
void loadFile(char **buffer, char *filename);

//-------------------------------------------
// getOptions()
// valeur de retour:
//  0: succès
//  -1: échec
// Boucle à travers le tableau d'arguemnts 
// et attribut les valeurs aux variables
// respectives ainsi que les options.
//-------------------------------------------
int getOptions(int,char**);

#endif /* end of include guard: ANALYSEUR_4BB0V0UD */