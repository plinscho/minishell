# minishell

/*	TOKENS	*/

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


Error codes:
2 - malloc fails
1 - fd fails
