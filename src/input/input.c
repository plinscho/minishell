#include "../../include/minishell.h"

void	char_an(const char *full_cmd)
{
	size_t	chars;
	char	*inp_cpy = NULL;
	size_t	n;

	n = 10;
	inp_cpy = ft_strndup(full_cmd, n);
	chars = ft_strlen(full_cmd);

//	TESTING FT_STRNDUP

	for (int i = 0 ; i <= 10 ; i++)
		printf("[%d]: %c\n", i, inp_cpy[i]);
	printf("\t[CHAR_AN]\n");
	printf("og: %s | size: %lu\n", full_cmd, chars);
	printf("cp: %s | n: %ld\n", inp_cpy, n);
	printf("\n");

	return ;
}