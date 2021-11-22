# include "../../minishell.h"

// int	remove_env(char ***envp, int pos)
// {
// 	char	**new;
// 	int	i;
// 	int	j;

// 	i = ft_strslen(envp);
// 	new = (char **)malloc(sizeof(char *) * i);
// 	if (!new)
// 		return (RET_FALSE); //malloc error
// 	i = 0;
// 	j = 0;
// 	while (envp[i])
// 	{
// 		if (i != pos)
// 			new[j++] = envp[i++];
// 		else
// 		{
// 	system("leaks minishell | grep leaked");

// 			ft_free(&envp[i]);
// 			i++;
// 		}
// 	}
// 	new[j] = NULL;
// 	// free(envp);
// 	system("leaks minishell | grep leaked");

// 	return (new);
// }

int	remove_env(char ***envp, int pos)
{
	int	i;
	int	last;

	last = ft_strslen(*envp);
	if (last < 1)
		return (RET_FALSE);
	i = -1;
	while ((*envp)[++i])
		if (i == pos)
		{
			printf("herer\n");
			ft_free(&(*envp)[i]);
			(*envp)[i] = ft_strdup((*envp)[last - 1]);
			printf("her222er\n");
			ft_free(&(*envp)[last - 1]);
			return (RET_TRUE);
		}
	return (RET_TRUE);
}

int	ft_unset(t_info *info, t_cmd *cur) //malloc error (export HHH ABC=123 -> export -> unset HHH ABC)
{
	int	i;
	int	env_pos;
	char	*tmp;

	i = -1;
	tmp = NULL;
	if (!cur->arg)
		return (RET_FALSE); //종료
	while (cur->arg[++i])
	{
		while (cur->arg[i] && cur->arg[i] != ' ')
			tmp = ft_charjoin(tmp, cur->arg[i++]);
		if (!tmp || (tmp[0] != '_' && !ft_isalnum(tmp[0]))) //tmp존재하지 않을떄?
		{
			info->code = 1;
			return (error_print("unset", cur->arg, "not a valid identifier", info));
		}
		env_pos = is_exist_env(tmp, info->envp);
		ft_free(&tmp);
		if (env_pos == -1)
			return (RET_FALSE); //그냥 종료
		remove_env(&info->envp, env_pos);
	}
	g_ret_number = 0;
	return (RET_TRUE);
}
