#include "../../include/minishell.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>

#define ERR_MLC	-2
#define ERR_KEY	-1
#define	NOTHING	0
#define UPDATE	1
#define ADD		2


int		print_export(t_env *etmp)
{
	t_env	*eprint;

	eprint = etmp;
	while (eprint)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(eprint->env_full, 1);
		ft_putstr_fd("\n", 1);
		eprint = eprint->next;
	}
	return (0);
}

char	*get_key(char *cmd_str, int *hasval)
{
	unsigned int	i;
	char			*new_key = NULL;
	
	i = 0;
	*hasval = 1;
	while (cmd_str[i] && cmd_str[i] != '=') 
		i++;
	if (cmd_str[i] == '\0')
		*hasval = 0;
	new_key = ft_strndup(cmd_str, i);
	if (!new_key)
		return (NULL);
	return (new_key);
}

char	*get_val(char *cmd_str)
{
	unsigned int	i;
	char			*val = NULL;

	i = 0;
	while (cmd_str[i] != '=')
		cmd_str++;
	cmd_str++;
	val = ft_strdup(cmd_str); // protect the ft_strdup
	if (!val)
		return (NULL);
	return (val);
}
/*
	FUNCTIONS FOR EXPORT
*/

int		has_equal_sign(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	make_env_full(t_env *node, char *key, char *val, char *full)
{
	ft_memdel(node->env_full);
	ft_memdel(node->env_key);
	ft_memdel(node->env_val);
	node->env_key = key;
	node->env_val = val;
	node->env_full = full;
}

// This var has value and its in env
int		env_update(t_mini *sh, char *var, t_env *head)
{
	t_env	*tmp;
	char	*new_val;
	char	*new_key;

	new_key = get_key(var, NULL);
	if (!new_key)
		return (ERR_KEY);
	tmp = ft_getkey_node(new_key, head);
	if (!tmp)
		return (ERR_MLC);
	new_val = ft_get_value(sh, new_key);
	if (!new_val)
		return (ERR_MLC);
	make_env_full(tmp, new_key, new_val, var);
}

void	ft_char_upd(t_mini *sh)
{
	char	**new_env;
	int		i;
	t_env	*tmp;

	arr_clean(sh->env, 0);
	new_env = (char **)malloc(sizeof(char *) * (env_variables(sh->env_lst, 2)));
	if (!new_env)
		return ;
	i = 0;
	tmp = sh->env_lst;
	while (tmp->next)
	{
		if (has_equal_sign(tmp->env_full))
		{
			new_env[i] = tmp->env_full;
			i++;
		}
		tmp = tmp->next;
	}
	sh->env = new_env;
}

t_env	*ft_envlast(t_env *lst)
{
	if (lst)
		while (lst -> next)
			lst = lst -> next;
	return (lst);
}

t_env	*ft_getkey_node(char *new_key, t_env *list)
{
	t_env	*head;
	
	head = list;
	while (list->next)
	{
		if (ft_strcmp(new_key, list->env_key) == 0)
			return (list);
		list = list->next;
	}
	list = head;
	return (NULL);

}

int		env_add(char *var, t_env *head)
{
	t_env	*tmp;
	t_env	*new;

	tmp = head;
	new = envnode_new(var);
	if (!new)
		return (1);
	ft_envlast(tmp);
	tmp->next = new;
	return (0);
}

int		key_in_env(char *new_key, t_env *env)
{
	t_env	*tmp;
	
	tmp = env;
	while (tmp->next)
	{
		if (ft_strcmp(new_key, tmp->env_key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		split_env(char *export, t_env *head)
{
	int		in_env;
	int		hasval;
	char	*new_key;

	hasval = 0;
	new_key = get_key(export, &hasval);
	if (!new_key)
		return (ERR_KEY);
	in_env = key_in_env(new_key, head);

	// If it exists and has value. Will be shown in char **env
	if (hasval && in_env)
		return (UPDATE);
	else if (!in_env)
		return (ADD);
	else
		return (NOTHING);
}

// 25 lines lol
int		ft_export(t_mini *sh)
{
	t_env	*tmp_env;
	char	**t_cmd;
	int		option;
	int		err;
	int		i;
	
	tmp_env = sh->env_lst;
	t_cmd = sh->pipe_lst->cmd;
	if (!t_cmd || !tmp_env)
		return (1);
	err = 0;
	i = -1;
	while (t_cmd[++i] != NULL)
	{
		option = split_env(t_cmd[i], tmp_env);
		if (option == ERR_KEY)
			return (ERR_KEY);
		else if (option == UPDATE)
			err = env_update(sh, t_cmd[i], tmp_env);
		else if (option == ADD)
			err = env_add(t_cmd[i], tmp_env);
		if (err)
			return (err);
		ft_char_upd(sh);
	}
	return (0);
}

