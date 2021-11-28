#include "../../minishell.h"

int	remove_env(char ***envp, int pos)
{
	int	i;
	int	last;

	last = ft_strslen(*envp);
	if (last < 1)
		return (RET_FALSE);
	i = -1;
	while ((*envp)[++i])
	{
		if (i == pos)
		{
			ft_free(&(*envp)[i]);
			(*envp)[i] = ft_strdup((*envp)[last - 1]);
			ft_free(&(*envp)[last - 1]);
			return (RET_TRUE);
		}
	}
	return (RET_TRUE);
}

int	ft_unset(t_info *info, t_cmd *cur)
{
	int	i;
	int	env_pos;

	i = -1;
	if (!cur->arg)
		return (RET_FALSE);
	while (cur->arg_token[++i])
	{
		if (!valid_env_name(cur->arg_token[i], 'u'))
			return (error_print("unset", cur->arg, \
			"not a valid identifier", 1));
		env_pos = is_exist_env(cur->arg_token[i], info->envp);
		remove_env(&info->envp, env_pos);
	}
	g_ret_number = 0;
	return (RET_TRUE);
}
