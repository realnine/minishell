#include "../minishell.h"

char	**add_arg_token(char **arg_token, char *arg)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (ft_strslen(arg_token) + 2));
	if (!new)
		return (NULL);
	if (!arg_token)
	{
		new[0] = arg;
		new[1] = NULL;
	}
	else
	{
		i = -1;
		while (arg_token[++i])
			new[i] = arg_token[i];
		new[i] = arg;
		new[++i] = NULL;
		free(arg_token);
	}
	return (new);
}

void	put_arg(t_info *info, t_cmd *cur, int i)
{
	char	*tmp;

	if (!cur->arg)
		cur->arg = ft_strdup(info->token[i]);
	else
	{
		tmp = cur->arg;
		cur->arg = ft_strjoin2(cur->arg, " ", info->token[i]);
		free(tmp);
	}
	cur->arg_token = add_arg_token(cur->arg_token, info->token[i]);
	if (!cur->arg_token)
		error_exit("malloc error\n", info);
}
