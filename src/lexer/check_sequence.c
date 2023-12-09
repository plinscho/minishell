/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:22:21 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/09 15:39:52 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
		TOKENS	

 The list of tokens:
0 = space; - content is null
1 = word;
2 = ' single quotes string;
3 = " double quotes string; 
4 = < infile redirection; - content is nullcheckout 
5 = > outfile redirection; - content is null
6 = << heredoc sign; IF THERE IS NO SINGLE QUOTES IN KEY WORD - content is null 
7 = >> outfile append redirection; - content is null
8 = | pipe; - content is null
9 = << heredoc sign; IF THERE IS ARE SINGLE QUOTES IN KEY WORD (SO NO EXPANTION INSIDE) - content is null 


// PARSER

# define EMPTY 0 
# define APPEND 3		>>
# define TRUNC 4		>
# define PIPE 5			|
# define INPUT 6		<
# define HERE_DOC 7		<<
# define END 8
# define REDIR 9
# define CMD 10
# define SCUOTE 39
# define DCUOTE 34
# define EXPORT "export %s=%s: not a valid identifier\n"
*/

int		no_cmd(char *seq)
{
	int	i;

	i = 0;
	while(seq[i])
	{
		if (!(ft_isspace(seq[i])))
			return (0);
		i++;
	}
	return (1);
}

int syntax_handler(t_lexer *head, int *pipes, int *redirs)
{
    int prev_token = -1;
    while (head)
    {
        if (head->token == 3 || head->token == 4 || head->token == 5)
        {
            if (prev_token == 3 || prev_token == 4 || prev_token == 5)
                return (err_char(prev_token));
            if (head->token == 5)
                *pipes += 1;
            else
                *redirs += 1;
            if (*pipes > 1 || *redirs > 2)
                return (err_char(head->token));
        }
        prev_token = head->token;
        head = head->next;
    }
    if (prev_token == 3 || prev_token == 4 || prev_token == 5)
        return (err_char(prev_token));
    return (0);
}


int check_syntax(t_mini *sh, t_lexer *lexer)
{
    t_lexer *current = lexer;
    int prev_token = -1;

    while (current != NULL)
    {
        if (current->token != 0) // Ignore space tokens
        {
            if (current->token >= 4 && current->token <= 9) // If the token is a pipe or redirection operator
            {
                if (prev_token >= 4 && prev_token <= 9) // If the previous token was also a pipe or redirection operator
                {
                    sh->exit = 258;
                    return (err_char(current->token)); // Return an error
                }
            }
            prev_token = current->token;
        }
        current = current->next;
    }
    if (prev_token >= 4 && prev_token <= 9) // If the last token was a pipe or redirection operator
    {
        sh->exit = 258;
        return (err_char(prev_token)); // Return an error
    }
    return 0; // No syntax errors found
}
/*

// Modify function, pair events are swallowed by the shell
int syntax_handler(t_lexer *head, int *pipes, int *redirs)
{
    while (head)
    {
        if (head && (head->token == 3 || head->token == 4))
        {
            if (*redirs >= 2) // Allow multiple redirections
                return (err_char(head->token));
            *redirs += 1;
        }
        if (head && head->token == 5)
        {
            if (*pipes >= 1 || *redirs >= 1)
                return (serror("|"));
            *pipes += 1;
        }
        if (head && (head->token == 6 || head->token == 7))
        {
            if (*redirs >= 2) // Allow multiple redirections
                return (err_char(head->token));
            *redirs += 1;
        }
        head = head->next;
    }
    return (0);
}
*/

/*		OLD CHECK SYNTAX

int	check_syntax(t_lexer *head) // meter el error 258 en la struct de la minishell.
{
	t_lexer	*tmp;
	int		pipes;
	int		redirs;

	tmp = head;
	if (tmp && tmp->token == 8)
		return (serror("|"));
	redirs = 0;
	pipes = 0;
	if (syntax_handler(tmp, &pipes, &redirs) != 0)
		return (2);
	if (redirs >= 1)
		return (serror("'newline'"));
	if (pipes >= 1)
		return (serror("|"));
	return (0);
}

*/
int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

char int_to_char(int num)
{
  return (char)(num + '0');
}