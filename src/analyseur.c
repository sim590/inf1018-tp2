//-------------------------------------------------------
// File: analyseur.c    Author(s): Simon Désaulniers
//                                 Frédéric Hamelin
// Date: 2013-11-11
//-------------------------------------------------------
// Fichier principale du projet inf1018-tp2
//-------------------------------------------------------
#include <analyseur.h>

void loadFile(char **buffer, char *filename)
{
    FILE *fp;
    long lSize;

    fp = fopen (filename , "rb" );
    if( !fp ) perror(filename),exit(1);

    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );

    *buffer = calloc( 1, lSize+1 );
    if( !*buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    if( 1!=fread( *buffer , lSize, 1 , fp) )
          fclose(fp),free(*buffer),fputs("entire read fails",stderr),exit(1);

    fclose(fp);
}

int getOptions(int argc, char* argv[])
{
    int opt, optindex = 0;
    static struct option long_options[] = {
        {"help"   , no_argument       , 0 , 'h' },
        {"lexems" , required_argument , 0 , 'l' },
        {0        , 0                 , 0 , 0   }
    };

    while ((opt = getopt_long(argc, argv, "hl:", long_options, &optindex)) != -1) {
        switch(opt){
            case 'h':
                printf("%s\n", HELP);
                exit(EXIT_SUCCESS);
            case 'l':
                if (optarg) {
                    lexems_filename = malloc(sizeof(char)*strlen(optarg));
                    strcpy(lexems_filename, optarg);
                }
                else {
                    fprintf(stderr, "%s\n", MISSING_ARG);
                    return -1;
                }
                break;
            default:
                fprintf(stderr, "%s\n", HELP);
                return -1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "%s\n", MISSING_ARG);
        return -1;
    }

    input_filename = malloc(sizeof(argc-optind));
    strcpy(input_filename, argv[optind]);

    return 0;
}


// Point d'entrée dans le programme
int main(int argc, char *argv[])
{
    // lecture des options et arguments nécessaires
    if (getOptions(argc, argv))
        exit(EXIT_FAILURE);
    // mise en tampon du fichier de test
    loadFile(&buffer, input_filename); 
    // mise en tampon du lexique
    loadFile(&lexems, lexems_filename);

    //lancement de l'analyse lexico-syntaxique
 
    exit(EXIT_SUCCESS);
}
