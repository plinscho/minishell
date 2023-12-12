/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:18:38 by plinscho          #+#    #+#             */
/*   Updated: 2023/12/12 16:21:41 by nzhuzhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expanser.h"

/*
type = 9 - no expansion
type = 6 - expansion type "" (3)
*/
char	*expand_hd(t_mini *sh, char *cont, int type)
{
	if (type == 9)
		return (cont);
	if (check_exp(cont, 3, -1) < 0)
		return (cont);
	if (exp_init(sh))
		return (0);
	cont = expand_str(sh, cont, 1, -1);
	return (cont);
}

/*
If type = 1 - It's a word (token 1)  0
if type = 3 - it's a string "" (token 3) 1
*/
char	*expand_str(t_mini *sh, char *cont, int type, int i)
{
//	printf("[EXP STR] entered exp str, cont-- %s\n", cont); //erase
//	printf("[EXP STR] final lenth -- %i\n", k); //erase
	if (exp_start(sh, cont, type))
		return (NULL);
	while (cont[++i])
	{
		if (cont[i] != '$' || !cont[i + 1])
			sh->exp->new[++sh->exp->j] = cont[i];
		else
		{
	//		printf("[EXP STR] entered else, str[i] -- %c\n", cont[i]); //erase
			sh->exp->var = get_var(&cont[i + 1]);
	//		printf("[EXP STR] var -- %s\n", sh->exp->var); //erase
			if (!sh->exp->var)
				return (NULL);
			sh->exp->val = check_value(sh, sh->exp->var);
			if (*sh->exp->var == '?' && !sh->exp->val)
				return (NULL);
			while (sh->exp->val && sh->exp->val[++sh->exp->k])
				sh->exp->new[++sh->exp->j] = sh->exp->val[sh->exp->k];
			i += ft_strlen(sh->exp->var);
	//		printf("[EXP STR] after get value, str[i] -- %c, str[i-1] -- %c\n", cont[i], cont[i - 1]); //erase
			exp_nano_clean(sh->exp);
		}
	}
	sh->exp->new[++sh->exp->j] = '\0';
	if (type == 3)
		sh->exp->cont = ft_memdel(sh->exp->cont);
	return (sh->exp->new);
}

t_lexer *read_word_exp(char *in, int *i, char q, int j)
{
	char	*cont;

//	printf("[EXP_RW]You entered: input - %s\n", in); //erase
	while (in[j] && in[j + 1] && check_chr(in[0]) == 2 && in[j + 1] != in[0])
		j++;
	if (in[j] && in[j + 1] && check_chr(in[0]) == 2)
		j = j + 2;
	while (in[j] && in[j + 1] && in[j + 1] != ' ' && check_chr(in[j + 1]) != 2)
		j++;
	while (in[j] && in[j + 1] && (in[j + 1] == '\'' || in[j + 1] == '\"'))
		j = word_in_quotes(in, &q, j);
//	printf("[RW] After iteration: input - %c, j - %i\n", in[j], j); //erase
//	if (q != ' ')
//		(*i)++;
	cont = ft_substr(in, 0, j + 1);
	if (cont)
		cont = trim_quotes(cont, ' ', ft_strlen(cont), -1);
	if (!cont)
		return (NULL);
	*i += j;
//	printf("[EXP RW] leaving, cont: %s, in[i] -- %c\n", cont, in[j]); //erase
	return (lex_new(cont, 1));
}

int		expand_word(t_mini *sh, t_lexer **lex)
{
	char	*str;
	t_lexer	*new;
	t_lexer	*head;
	int		i;

	str = expand_str(sh, sh->lex_lst->cont, 1, -1);
//	printf("--------------- \n[EXP WORD] in sh lex node: \n"); //erase
//	print_lex_node(sh->lex_lst); //erase
//	printf("--------------- \n[EXP WORD] free lex node: \n"); //erase
//	print_lex_node(lex); //erase
//	printf("[EXP_WORD] expanded string: %s|\n", str); //erase
	if (!str)
		return (1);
	head = NULL;
//	printf("[EXP_WORD] old lex: %p, new lex; %p\n", lex, head); //erase
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			new = read_space(&str[i], &i);
		else
			new = read_word_exp(&str[i], &i, ' ', 0);
		if (!new)
			return (1);
		else
			lex_add(&head, new);
	}
//	printf("--------------- \n[EXP WORD] lex node: \n"); //erase
//	print_lex_node(head); //erase
	lex_insert(sh, head, lex);
//	printf("--------------- \n[EXP WORD] after insert: \n"); //erase
//	print_lex_node(head); //erase
//	printf("--------------- \n[EXP WORD] AFTER ALL in sh lex node: \n"); //erase
//	print_lex_node(sh->lex_lst); //erase
//	printf("--------------- \n[EXP WORD] AFTER ALL free lex node: \n"); //erase
//	print_lex_node(lex); //erase
//	printf("1\n");
//	lex_last(*lex)->next = old->next;
//	old->next = NULL;
	str = ft_memdel(str);
//	printf("2\n");
//	trim quotes here??? no, cause there are strings where no exp but quotes
//	trim quotes in parser? expand filename in parser??
//	return (lex_clean(&old));
	return (0);
}

/*
	Function designed to expand the $ into the command.
*/
int	expanser(t_mini *sh, t_lexer *head)
{
	int	flag;

	flag = 0;
	if (exp_init(sh))
		return (0);
	while (sh->lex_lst)
	{
	//	printf("\n --------------- \n[EXPANSE] start loop \n"); //erase
	//	print_lex_node(sh->lex_lst); //erase
	//	printf("[EXPANSE] cont: %i\n", check_exp(sh->lex_lst->cont, 1)); //erase
	//	printf("[EXPANSE] get value $0: %s\n", ft_get_value(sh, "0")); //erase
		if (sh->lex_lst->token == 3 && sh->lex_lst->cont && \
		check_exp(sh->lex_lst->cont, 3, -1) != -1)
		{
	//		printf("[EXPANSE] BEFORE EXP STRING content: %s\n", sh->lex_lst->cont); //erase
			sh->lex_lst->cont = expand_str(sh, sh->lex_lst->cont, 3, -1);
			if (!sh->lex_lst->cont)
				return (err_break(sh_restore(&sh, head, NULL), "malloc", NULL, 12));
		}
		else if (sh->lex_lst->token == 1 && check_exp(sh->lex_lst->cont, 1, -1) >= 0 && !flag)
		{	
			if (expand_word(sh, &head))
				return (err_break(sh_restore(&sh, head, NULL), "malloc", NULL, 12));
		}
		else if (sh->lex_lst->token == 1 && check_exp(sh->lex_lst->cont, 1, -1) < 0 && !flag)
		{
			sh->lex_lst->cont = trim_quotes(sh->lex_lst->cont, ' ', ft_strlen(sh->lex_lst->cont), -1);
			if (!sh->lex_lst->cont)
				return (err_break(sh_restore(&sh, head, NULL), "malloc", NULL, 12));
		}
		else if (sh->lex_lst->token > 3 && sh->lex_lst->token < 8)
			flag = 1;
		if (sh->lex_lst && sh->lex_lst->token > 0 && sh->lex_lst->token < 4 && flag)
			flag = 0;
	//	printf("\n --------------- \n[EXPANSE] lex node: \n"); //erase
	//	printf("pointer: %p\n", sh->lex_lst);
	//	print_lex_node(sh->lex_lst); //erase
		if (sh->lex_lst)
		{
	//		printf("[EXPANSE] before next: \n"); //erase
			sh->lex_lst = sh->lex_lst->next;
		}
	}
//	printf("[EXPANSE] before next: \n"); //erase
	sh_restore(&sh, head, NULL);
//	printf("[EXPANSE] leaving, pointer to head: %p\n", head); //erase
//	exit (1); //erase
	return (0);
}