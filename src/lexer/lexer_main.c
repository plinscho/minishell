/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:33:36 by nzhuzhle          #+#    #+#             */
/*   Updated: 2023/11/11 19:50:25 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


t_lexer *read_space(char *in, int *i)
{
	int	j;

	j = 0;
	while (in[j + 1] && in[j + 1] == ' ')
        j++;
	*i += j;
    return(lex_new(NULL, 0));
}
/* I dont interpret the \\ like in bash -- see the subject */
t_lexer *read_word(char *in, int *i)
{
	char	*cont;
	int		j;
	char	q;

	j = 0;
	while (in[j] && in[j] != ' ' && in[j] != '\'' && in[j] != '\"' \
	&& check_chr(in[j]))
		j++;
	if (in[j] && (in[j] == '\'' || in[j] == '\"'))
	{
		q = in[j];
		j++;
		while (in[j] && in[j] != q)
			j++;
		while (in[j] && in[j + 1] && in[j + 1] != ' ')
			j++;
		cont = ft_substr_quotes(in, q, j, -1);
		(*i)++;
	}
	else
		cont = ft_substr(in, 0, j);
	if (!cont)
		return (NULL);
	*i += j - 1;
	return (lex_new(cont, 1));
}

/* I dont interpret the \\ like in bash -- see the subject */
t_lexer *read_in_quotes(char *in, int *i)
{
	char	*cont;
	int		j;

	j = 0;
//	printf("entered read quotes: i == %i\n", *i);
	while (in[j] && in[j + 1] != in[0])
		j++;
	cont = ft_substr(in, 1, j);
	if (!cont)
		return (NULL);
	*i += j + 1;
//	printf("in read quotes: i == %i\n", *i);
	if (in[0] == '\'')
		return (lex_new(cont, 2));
	else
		return (lex_new(cont, 3));
	
}

t_lexer *read_redirection(char *in, t_mini *sh, int *i)
{
    int j;

    j = 0;
    if (in[j] == '<' && in[j + 1] != '<') // the case of < input file
        return (lex_new(NULL, 4));
    else if (in[j] == '>' && in[j + 1] != '>') // the case of > output file
        return (lex_new(NULL, 5));
    else if (in[j] == '<' && in[j + 1] == '<') // the case of << heredoc
    {
        (*i)++;
        return (lex_new(NULL, 6));
    }
    else if (in[j] == '>' && in[j + 1] == '>') // the case of >> append
    {    
        (*i)++;
        return (lex_new(NULL, 7));
    }
    else if (in[j] == '|')
	{
		sh->pipes++;
		return (lex_new(NULL, 8));
	}
	return (NULL);
}

int lexer(char *input, t_mini *sh, t_lexer **head)
{
    t_lexer *new;
    int i;

    i = -1;
    new = NULL;
    while (input[++i])
    {
        if (input[i] == ' ')
            new = read_space(&input[i], &i);
        else if (input[i] == '<' || input[i] == '>' || input[i] == '|')
            new = read_redirection(&input[i], sh, &i);
        else if (input[i] == '\'' || input[i] == '\"')
			new = read_in_quotes(&input[i], &i);
		else
			new = read_word(&input[i], &i);
		if (!new)
			return (sh_clean(&sh, 2));
		else
			lex_add(head, new);
    }
	return (0);
}

/*int main(int argc, char **argv, char **envp)
{
    char    *input = NULL;
	t_lexer *lex_list = NULL;
	t_hd	*hd = NULL;
//	char	**cp_env = NULL; 
    int i;

	if (argc != 1 && argv[0])
		return (1);
//	cp_env = cpy_env(envp);
//	if (!cp_env)
//		return (1);
	while (42)
	{
		input = readline("minishell> ");  
        if (!input) // in case we recieved an empty line
            break;
		if (ft_here_doc(input, &hd))
			return (1); // exit code malloc error
//		printf("[MAIN]You entered: %s\n\n", input);
		if (lexer(input, &lex_list)) // it means that a malloc failed, my lex_clean cleaned input and list
			return (1);
		i = 1;
    	while (lex_list)
    	{
			printf("lexer node %i -- content: %s, type; %i\n", i, lex_list->cont, lex_list->token); //erase
       	 	i++;
        	lex_list = lex_list->next; 
    	}
		i = 1;
		while (hd)
    	{
			printf("hd node %i -- key: %s, fd: %i\n", i, hd->str, hd->fd); //erase
       	 	i++;
        	hd = hd->next; 
    	}
	}
	lex_clean(&lex_list, &input);
	return (0);
}*/