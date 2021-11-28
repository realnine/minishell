#include "../../minishell.h"

int	is_designate(char *arg)
{
	return (!arg || !ft_strcmp("~", arg) || !ft_strcmp("~/", arg) \
	|| !ft_strcmp("-", arg) || !ft_strncmp("$", arg, 1));
}

int	dir_designate(char *path, t_cmd *cur, t_info *info)
{
	if (!cur->arg || !ft_strcmp("~", cur->arg) || !ft_strcmp("~/", cur->arg))
	{
		if (!dir_home(path, cur->arg, info))
			return (RET_FALSE);
	}
	else if (!ft_strcmp("-", cur->arg))
	{
		if (!dir_oldpwd(cur, path, info))
			return (RET_FALSE);
	}
	else if (!ft_strncmp("$", cur->arg, 1))
	{
		if (!dir_env(path, cur->arg, info))
			return (RET_FALSE);
	}
	return (RET_TRUE);
}

void	dir_start_home(char *path, char *arg, char **envp)
{
	int		i;
	int		j;
	char	*env_val;

	env_val = find_env_val("HOME", envp);
	i = -1;
	while (env_val[++i])
		path[i] = env_val[i];
	j = 1;
	while (arg[j])
		path[i++] = arg[j++];
}

char	**add_env(char **envp, char *str)
{
	char	**new;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = -1;
	while (envp[++i])
		new[i] = envp[i];
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	free(str);
	free(envp);
	return (new);
}

int	ft_cd(t_info *info, t_cmd *cur)
{
	char	path[PATH_MAX + 1];
	int		i;
	int		len;

	len = ft_strlen(cur->arg);
	i = -1;
	ft_memset(path, 0, sizeof(path));
	if (is_designate(cur->arg))
	{
		if (!dir_designate(path, cur, info))
			return (RET_FALSE);
	}
	else if (cur->arg[0] == '~' && cur->arg[1] == '/' && len > 2)
		dir_start_home(path, cur->arg, info->envp);
	else
		while (cur->arg[++i])
			path[i] = cur->arg[i];
	dir_move(path, &info->envp);
	return (RET_TRUE);
}
