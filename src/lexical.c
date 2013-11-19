//-------------------------------------------------------
// File: lexical.c    Author(s): Simon Désaulniers
//                               Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Gestion des tâches lexicales de l'analyseur
//-------------------------------------------------------
#include "lexical.h"


void loadFile(char *filename)
{
    FILE *fp;
    long lSize;

    fp = fopen (filename , "rb" );
    if( !fp ) perror(filename),exit(1);

    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );

    /* allocate memory for entire content */
    buffer = calloc( 1, lSize+1 );
    if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    /* copy the file into the buffer */
    if( 1!=fread( buffer , lSize, 1 , fp) )
          fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

    /* do your work here, buffer is a string contains the whole text */
    fclose(fp);
    free(buffer);
}

char * next()
{
    int strLength = 0;

    while(*buffer != '\0') {
        if ((*buffer == ' ' || *buffer == '\n' || *buffer == '\t' )) {
            if (strLength != 0)
                return getLastCharacters(strLength);
            else
                buffer++;
        }
        else if (*buffer == '+' || *buffer == '-' || *buffer == '*' || *buffer == '/' 
                    || *buffer == ':' || *buffer == ';' || *buffer == '(' || *buffer == ')') {
           if (strLength == 0) {
                char * token = malloc(sizeof(char) * 2);

                *token = *buffer;

                buffer++;
                token++;

                *token = '\0';

                lastTokenSize = 1;
                return token;
           }
           else {
                return getLastCharacters(strLength);
           } 
        }
        else {
            strLength++;
            buffer++;
        }
    }

    lastTokenSize = 0;
    return "";
}

char * last()
{
    char * token = getLastCharacters(lastTokenSize);

    buffer -= lastTokenSize;

    return token;
}

char * getLastCharacters(int strLength)
{
    char * token = malloc(sizeof(char) * (strLength + 1));

    buffer -= strLength;

    int index = 0;

    while (index < strLength) {
        *token = *buffer;
        buffer++;
        token++;
        index++;
    }

    *token = '\0';

    token -= strLength;

    lastTokenSize = strLength;
    return token;
}
