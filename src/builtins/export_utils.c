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
		ft_putstr_fd("declare -x ", 2);
		ft_putstr_fd(eprint->env_full, 1);
		ft_putstr_fd("\n", 1);
		eprint = eprint->next;
	}
	return (0);
}

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


