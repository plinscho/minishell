#include "../../include/minishell.h"

int main(int argc, char **argv)
{
//   char    *input = NULL;
	t_lexer *lex_list = NULL;
//	t_pipe	*parse = NULL;
//	t_hd	*hd = NULL;
	t_mini	*sh;
//	char	**cp_env = NULL; 
	int i;

	if (argc != 1 && argv[0])
		return (1);
//	cp_env = cpy_env(envp);
//	if (!cp_env)
//		return (1);
	sh = malloc(sizeof(t_mini));
	if (!sh)
		return (1); // break the loop with the needed exit status
	mini_init(sh); // parse the envp here????
	while (42)
	{
		sh->input = readline("minishell> ");
        if (!sh->input) // in case we recieved an empty line
            break;
//		Here we add a prelexer that will destroy the input str if any open quote and write the error message
		if (ft_here_doc(&sh, sh->input, &(sh->hd_lst)))
			break ; // break the loop code malloc error return (ft_error)
//		printf("[MAIN]You entered: %s\n\n", input);
//		Here we add a prelexer that checks all the syntax errors and if there is anything except spaces
		if (lexer(sh->input, &sh, &(sh->lex_lst))) // it means that a malloc failed, my lex_clean cleaned input and list
			break ; // we should clean the heredoc 
		i = 1;
		lex_list = sh->lex_lst;
		while (lex_list)
    	{
			printf("node %i -- content: %s, type; %i\n", i, lex_list->cont, lex_list->token); //erase
       	 	i++;
        	lex_list = lex_list->next; 
    	}
		if (parser(&sh, sh->lex_lst, sh->hd_lst, 0))
			break ; //we should clean all - I do it in the parser + we should write an error message function 
		i = 0;
		/*while (sh->pipe_lst)
    	{
			printf("pipe %i -- cmd: %p, fd: %p\n", i, sh->pipe_lst->cmd, sh->pipe_lst->fd_lst); //erase
       	 	i++;
        	sh->pipe_lst = sh->pipe_lst->next; 
    	}*/
		sh_clean(&sh, 0);
	}
	return (0);
}