#include "include/minishell.h"

int main(void)
{
	char	*input = NULL;

	while (1)
	{
		input = readline("Minishell> ");
		if (!input)
			break ;
		printf("your line: %s\n", input);
		if (input && *input)
			add_history(input);
		free(input);
	}
	return (0);
}