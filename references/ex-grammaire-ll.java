static void expression()
{
    terme(); // Analyse du premier terme
    while ( next_token == code_plus || next_token == code_moins)
    {
        lexical(); // prendre le prochain token
        terme(); // analyse du prochain terme
    }
}

static void terme()
{
    facteur(); // analyse du premier facteur
    while (next_token == code_mult || next_token == code_div )
    {
        lexical(); // lecture du prochain token de l'entree
        facteur(); // analyse du prochain token
    }
}

static void facteur()
{
    if (next_token == token_identificateur){
        lexical(); 
        return;
    }
    else if (next_token == code_parenthese_gauche)
    {
        lexical(); 
        expression();

        if (next_token == code_parenthese_droite){
            lexical(); 
            return;
        } 
        else
            erreur(code_erreur) // parenthese droite oubliee 
    }
    else
        erreur(code_erreur) // ni un identificateur ni une parenthese gauche
}
