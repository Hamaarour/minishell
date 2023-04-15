#include <stdio.h>
#include <string.h>
typedef struct s_lexer
{
    char *src; // the string to be tokenized
    char c;    // current char in the string
    int i;     // index of the current char in the string
    int len_src;
} t_lexer;

void advance_lexer(t_lexer *lexer)
{
    if (lexer->i < lexer->len_src && lexer->c != '\0')
    {
        lexer->i++;
        lexer->c = lexer->src[lexer->i];
    }
}

int main()
{
    char source_string[] = "Hello,   World!";
    t_lexer lexer;
    lexer.src = source_string;
    lexer.i = 0;
    lexer.len_src = strlen(source_string);
    lexer.c = lexer.src[lexer.i];

    printf("Source string: %s\n", lexer.src);

    while (lexer.c != '\0')
    {
        printf("Current character: %c\n", lexer.c);

        advance_lexer(&lexer);
    }

    return 0;
}
