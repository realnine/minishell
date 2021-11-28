#include "../../minishell.h"

char	*find_env_val(char *name, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(name, envp[i], len))
			if (envp[i][len] == '=')
				return (ft_strchr(envp[i], '=') + 1);
	}
	return (NULL);
}

char	*cut_env_name(char *arg, int *i)
{
	int		len;
	char	*res;

	len = 0;
	while (arg[len] && (ft_isalpha(arg[len]) \
	|| arg[len] == '_' || arg[len] == '?'))
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		error_print("malloc error", NULL, NULL, 0);
	ft_memcpy(res, arg, len);
	res[len] = '\0';
	*i += len - 1;
	return (res);
}

void	exit_execve(t_info *info, t_cmd *cur)
{
	error_print(cur->cmd, "no such file or directory", NULL, 1);
	exit_free(info);
	exit(127);
}

int	valid_env_name(char *s, int flag)
{
	int	i;

	if (s[0] != '_' && !ft_isalpha(s[0]))
		return (RET_FALSE);
	if (flag == 'u')
	{
		i = -1;
		while (s[++i])
		{
			if (s[i] == '=')
				return (RET_FALSE);
		}
	}
	return (RET_TRUE);
}
