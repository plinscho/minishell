#include "../include/minishell.h"

int main(void)
{
    char    *input = NULL;
    
    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;
		printf("[MAIN]You entered: %s\n\n", input);
//		char_an(input);
        if (input && *input)
            add_history(input);
		char_an(input);
		signal_mgr();
        free(input);
    }
    return (0);
}