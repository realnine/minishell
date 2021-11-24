# include "../../minishell.h"

int	ft_strslen(char **strs)
{
	int	len;

	len = 0;
	if (!strs)
		return (0);
	while (strs[len])
		len++;
	return (len);
}

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

char	**sort_export(char **envp)
{
	char	**copy;
	char	*tmp;
	int		i;
	int		j;

	copy = (char **)malloc(sizeof(char *) * (ft_strslen(envp) + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (envp[++i])
		copy[i] = ft_strdup(envp[i]);
	copy[i] = NULL;
	while (--i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(copy[j], copy[j + 1]) > 0)
			{
				tmp = copy[j + 1];
				copy[j + 1] = copy[j];
				copy[j] = tmp;
			}
			j++;
		}
	}
	return (copy);
}

int	set_export_print(t_cmd *cur, char **envp)
{
	char	**sorted;
	char	*env_val;
	char	*env_name;
	char	*str;
	int	i;
	int	trash;

	sorted = sort_export(envp);
	i = -1;
	while (sorted[++i])
	{
		str = ft_strdup("declare -x ");
		env_name = cut_env_name(sorted[i], &trash); //trash?
		str = ft_strjoin_free(str, env_name, 1);
		env_val = find_env_val(env_name, sorted);
		if (env_val)
		{
			str = ft_strjoin_free(str, "=\"", 1);
			str = ft_strjoin_free(str, env_val, 1);
			str = ft_charjoin(str, '\"');
		}
		ft_putstr_fd(str, cur->fd_out);
		ft_putchar_fd('\n', cur->fd_out);
		ft_free(&env_name);
		env_val = NULL;
	}
	i = -1;
	while(sorted[++i])
		ft_free(&sorted[i]);
	free(sorted);
	sorted = NULL;
	return (RET_TRUE);
}

char	*ft_charjoin(char *str, char c)
{
	char	*new;
	int	len;
	int	i;

	len = ft_strlen(str);
	if (c == '\n')
		return (str);
	else
	{
		new = (char *)malloc(sizeof(char) * (len + 2));
		i = -1;
		if (str == NULL)
			new[0] = c;
		else
		{
			while (str[++i])
				new[i] = str[i];
			new[i] = c;
			ft_free(&str);
		}
		new[len + 1] = '\0';
	}
	return (new);
}

char	*export_etc(char *arg, char **envp, char *str)
{
	char	*env_name;
	char	*env_val;
	int	i;

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

int		is_exist_env(char *name, char **envp)
{
	int	i;
	const int	len = ft_strlen(name);

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
	int	pos;
	int	i;

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

int	valid_env_name(char *s, int flag)
{
	int	i;

	if (s[0] != '_' && !ft_isalnum(s[0]))
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

int	ft_export(t_info *info, t_cmd *cur) //(0)
{
	int	i;

	i = -1;
	if (!cur->arg) //cur->arg_token[0]으로 가능? 할당되어 잇을까?
		return (set_export_print(cur, info->envp));
	else
	{
		while (cur->arg_token[++i])
		{
			if (!valid_env_name(cur->arg_token[i], 'e'))
				return (error_print("export", cur->arg, strerror(errno), 1));
			add_export(cur->arg_token[i], &info->envp);
		}
	}
	g_ret_number = 0;
	return (RET_TRUE);
}