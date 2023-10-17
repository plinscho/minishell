#include "../../include/minishell.h"

void	char_an(const char *full_cmd)
{
	size_t chars;

	chars = ft_strlen(full_cmd);
	printf("[CHAR_AN] size: %lu\n", chars);
	return ;
}