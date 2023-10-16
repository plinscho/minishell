#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main(void)
{
	char	*input = NULL;

	while (1)
	{
		input = readline("Minishell_> ");
		if (!input)
			break ;
		printf("your line: %s\n", input);
		if (input && *input)
			add_history(input);
		free(input);
	}
	return (0);
}