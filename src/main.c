#include "../include/minishell.h"

int main(void)
{
    char    *input = NULL;
    t_lexer *lex_list;

    lex_list = NULL;
    while (1)
    {
        input = readline("minishell> ");
        if (!input || *input == '\0') // in case we recieved an empty line
            break;
		printf("[MAIN]You entered: %s\n\n", input);
        lex_list = lexer(input);
//		char_an(input);
        if (input && *input)
            add_history(input);
		char_an(input);
		signal_mgr();
        free(input);
    }
    return (0);
}