/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:18:38 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/20 22:44:11 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expanser.h"

int		check_word(char *word)
{
	
	
}


/*
	This function checks the lexer nodes that are stored as a 1.
	The idea is to check if the syntax is correct. Like ech@o or stuff like that.
	*/
int		get_words(t_lexer *lex)
{
	t_lexer	*tmp = NULL;
	int		check;

	check = 0;
	tmp = lex;
	while (tmp)
	{
		if (lex->token == '1')
			check = check_word(tmp->cont);
		tmp = tmp->next;
	}
	
		
}
int		w_syntax(t_mini *sh)
{
	int	words;

	words = get_words(sh->lex_lst);
	
	
	return (0);
}	



/*
	Function designed to expand the $ into the command, will be using the parser.
	
*/
int	expanser(t_mini *sh)
{
	
	return (0);
}