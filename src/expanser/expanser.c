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
		// Maybe we can use another number for the words that will be comands
		if (lex->token == '1')
			check = check_word(tmp->cont);
		
		//	I made up this token number for the $ operators. Tell Dina.
		else if (lex->token == 10)
			check = check_var(tmp->cont);
		tmp = tmp->next;
	}
	
	// This function returns the exit code. 
	// It returns to w_syntax so that it can save the error in the sh.
	return (check);
}

/*
	This function checks for syntax errors.
	The ideal would be to use it after the lexer, so that we know
	which words are comands and which are just file names or input.
	w_syntax also gets a error code from get_words and if != 0, 
	that means some syntax error is made.
	We can use that to populate sh->exit.
*/
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