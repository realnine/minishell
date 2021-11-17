# include "../../minishell.h"

char	**remove_env(char **envp, int pos)
{
	char	**new;
	int	i;
	int	j;

	i = 0;
	while (envp[i])
		i++;
	new = (char **)malloc(sizeof(char *) * i);
	if (!new)
		return (RET_FALSE); //malloc error
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (i != pos)
			new[j++] = envp[i++];
		else
		{
			free(envp[i]);
			i++;
		}
	}
	new[j] = NULL;
	free(envp);
	return (new);
}

int	ft_unset(t_info *info, t_cmd *cur)
{
	int	i;
	int	env_pos;

	i = -1;
	if (!cur->arg)
		return (RET_FALSE); //종료
	while (cur->arg[++i])
	{
		if (cur->arg[i] != '_' && !ft_isalnum(cur->arg[i]))
		{
			info->code = 1;
			return (error_print("unset", cur->arg, "not a valid identifier", info));
		}
	}
	env_pos = is_exist_env(cur->arg, info->envp);
	if (env_pos == -1)
		return (RET_FALSE); //그냥 종료
	info->envp = remove_env(info->envp, env_pos);
	g_ret_number = 0;
	return (RET_TRUE);
}
