# include "../../minishell.h"

int	is_export_normal(t_cmd *cur)
{
	int	i;

	i = -1;
	while (cur->arg[++i])
	{
		if (cur->arg[i] == '$')
			return (i);
	}
	return (-1);
}

char	**copy_envp(char **envp, int add)
{
	char	**new;
	int	i;

	i = 0;
	while (envp[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + add));
	if (!new)
		return (NULL);//에러 문장 보내기
	i = -1;
	while (envp[++i])
		new[i] = envp[i];
	new[i] = NULL;
	return (new);
}

char	**sort_export(char **envp)
{
	char	**copy;
	char	*tmp;
	int		i;
	int		j;

	copy = copy_envp(envp, 1);
	i = 0;
	while (copy[i])
		i++;
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
	i = -1;
	return (copy);
}

void	set_export_print(t_cmd *cur, char **envp, t_info *info)
{
	char	**sorted;
	char	*env_val;
	char	*env_name;
	int	i;
	int	trash;

	sorted = sort_export(envp);
	i = -1;
	while (sorted[++i])
	{
		ft_putstr_fd("declare -x ", cur->fd_out);
		env_name = cut_env_name(sorted[i], &trash, info); //trash?
		ft_putstr_fd(env_name, cur->fd_out);
		env_val = find_env_val(env_name, sorted);
		ft_putstr_fd("=\"", cur->fd_out); //export HHH= 과 export HHH 는 다르다,,,,(수정)
		ft_putstr_fd(env_val, cur->fd_out);
		ft_putchar_fd('\"', cur->fd_out);
		ft_putchar_fd('\n', cur->fd_out);
		// ft_free(&sorted[i]);
		ft_free(&env_name);
	}
	free(sorted);
	sorted = NULL;
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

char	*export_etc(char *arg, char **envp, char *str, t_info *info)
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
			env_name = cut_env_name(arg + i, &i, info);
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

void	add_export(t_cmd *cur, char ***envp, t_info *info)
{
	char	*str;
	int	pos;
	int	i;

	i = 0;
	str = cut_env_name(cur->arg, &i, info);
	printf("str = [%s]\n", str);

	pos = is_exist_env(str, *envp);
	if (is_export_normal(cur) == -1)
		str = ft_strjoin_free(str, cur->arg + i + 1, 1);
	else
		str = export_etc(cur->arg + i + 1, *envp, str, info);
	printf("str = [%s]\n", str);
	
	if (pos == -1)
	{
		*envp = add_env(*envp, str);
		printf("new-\n");
	}
	else
	{
		ft_strlcpy((*envp)[pos], str, ft_strlen(str) + 1);
		printf("new+\n");
		ft_free(&str);
	}
	printf("str = [%s]\n", str);
	// free(*envp);
	system("leaks minishell | grep leaked");

}

int	ft_export(t_info *info, t_cmd *cur)
{

	if (!cur->arg)
		set_export_print(cur, info->envp, info);
	else
	{
		if (cur->arg[0] != '_' && !ft_isalnum(cur->arg[0])) //env 조건 확인
		{
			info->code = 1; //추추
			return (error_print("export", cur->arg, "not a valid identifier", info));
		}
		add_export(cur, &info->envp, info);
	}
	g_ret_number = 0;
	return (RET_TRUE);
}
