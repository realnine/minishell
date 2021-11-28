#include "../../minishell.h"

int	is_export_normal(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '$')
			return (i);
	}
	return (-1);
}

char	*export_etc(char *arg, char **envp, char *str)
{
	char	*env_name;
	char	*env_val;
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] && arg[i + 1] != '\0')
		{
			i++;
			env_name = cut_env_name(arg + i, &i);
			env_val = find_env_val(env_name, envp);
			str = ft_strjoin_free(str, env_val, 1);
			ft_free(&env_name);
		}
		else
			str = ft_charjoin(str, arg[i]);
		i++;
	}
	return (str);
}

int	is_exist_env(char *name, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = -1;
	while ((envp[++i]))
	{
		if (!ft_strncmp(name, envp[i], len))
			return (i);
	}
	return (-1);
}

int	add_export(char *arg, char ***envp)
{
	char	*str;
	int		pos;
	int		i;

	i = 0;
	str = cut_env_name(arg, &i);
	pos = is_exist_env(str, *envp);
	if (is_export_normal(arg) == -1)
		str = ft_strjoin_free(str, arg + i + 1, 1);
	else
		str = export_etc(arg + i + 1, *envp, str);
	if (pos == -1)
		*envp = add_env(*envp, str);
	else
	{
		ft_strlcpy((*envp)[pos], str, ft_strlen(str) + 1);
		ft_free(&str);
	}
	return (RET_TRUE);
}

int	ft_export(t_info *info, t_cmd *cur)
{
	int	i;

	i = -1;
	g_ret_number = 0;
	if (!cur->arg_token)
		return (set_export_print(cur, info->envp));
	else
	{
		while (cur->arg_token[++i])
		{
			if (!valid_env_name(cur->arg_token[i], 'e'))
				error_print("export", cur->arg_token[i], \
				"not a valid identifier", 1);
			add_export(cur->arg_token[i], &info->envp);
		}
	}
	return (RET_TRUE);
}
