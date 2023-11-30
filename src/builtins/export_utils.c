#include "../../include/env.h"

#define ERR_KEY	-1
#defie	NOTHING	0
#define UPDATE	1
#define ADD		2

int		key_in_env(char *key, t_env *env)
{
	t_env	*tmp;
	
	tmp = env;
	while (tmp->next)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		split_env(char *export, t_env *head)
{
	int		in_env;
	int		hasval;
	char	*key;

	hasval = 0;
	key = get_key(export, &hasval);
	if (!key)
		return (ERR_KEY);
	in_env = key_in_env(key, head);
	
	// If it exists and has value. Will be shown in char **env
	if (hasval && in_env)
		return (UPDATE);
	else if (!in_env)
		return (ADD);
	else
		return (NOTHING);
}

int		ft_export_(t_mini *sh)
{
	t_env	*tmp_env;
	char	**t_cmd;
	int		option;
	int		err;
	int		i;
	
	tmp_env = sh->env_lst;
	t_cmd = sh->pipes->cmd;
	if (!t_cmd || !tmp_env)
		return (1);
	err = 0;
	i = 0;
	while (t_cmd[i] != NULL)
	{
		option = split_env(t_cmd[i], tmp_env);
		if (option == ERR_KEY)
			return (ERR_KEY);
		else if (option == UPDATE)
			err = env_update(t_cmd[i], head));
		else if (option == ADD)
			err = env_add(t_cmd[i], head);
		if (err)
			return (err);
		i++;
	}
	return (0);
}