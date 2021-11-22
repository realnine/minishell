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

char	**copy_envp(char **envp, int add)
{
	char	**new;
	int	i;

	i = ft_strslen(envp);
	new = (char **)malloc(sizeof(char *) * (i + add));
	if (!new)
		return (NULL);//에러 문장 보내기
	i = -1;
	while (envp[++i])
		new[i] = envp[i];
	new[i] = NULL;
	return (new);
}

char	**sort_export(char **envp)// 포인ㄴ터 개 난장판~ 정렬 수정하기
{
	char	**copy;
	char	*tmp;
	int		i;
	int		j;

	copy = (char **)malloc(sizeof(char) * (ft_strslen(envp) + 1));
	i = -1;
	while (envp[++i])
		copy[i] = ft_strdup(envp[i]);
	copy[i] = NULL;
	i = -1;
	while (copy[++i])
	{
		printf("copy = [%s]\n", copy[i]);
	} //왜깨져,,?
	
	// copy = copy_envp(envp, 1);
	// i = ft_strslen(envp);
	while (--i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(copy[j], copy[j + 1]) > 0)
			{
				printf("here\n");
				tmp = copy[j + 1];
				copy[j + 1] = copy[j];
				copy[j] = tmp;
			}
			j++;
		}
	}
	return (copy);
}

void	set_export_print(t_cmd *cur, char **envp, t_info *info)
{
	char	**sorted;
	// char	*env_val;
	// char	*env_name;
	int	i;
	// int	trash;

	sorted = sort_export(envp);
	i = -1;
	printf("=============================\n");
	while (sorted[++i])
	{
		printf("%d = [%s]\n", i, sorted[i]);
		ft_free(&sorted[i]);
	}
	(void)info;
	(void)cur;
	// while (sorted[++i])
	// {
	// 	ft_putstr_fd("declare -x ", cur->fd_out);
	// 	env_name = cut_env_name(sorted[i], &trash, info); //trash?
	// 	ft_putstr_fd(env_name, cur->fd_out);
	// 	env_val = find_env_val(env_name, sorted);
	// 	ft_putstr_fd("=\"", cur->fd_out); //export HHH= 과 export HHH 는 다르다,,,,(수정)
	// 	ft_putstr_fd(env_val, cur->fd_out);
	// 	ft_putchar_fd('\"', cur->fd_out);
	// 	ft_putchar_fd('\n', cur->fd_out);
	// 	// ft_free(&sorted[i]);
	// 	ft_free(&env_name);
	// }
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

int	add_export(char *arg, char ***envp, t_info *info)
{
	char	*str;
	int	pos;
	int	i;

	i = 0;
	str = cut_env_name(arg, &i, info);
	pos = is_exist_env(str, *envp);
	if (is_export_normal(arg) == -1)
		str = ft_strjoin_free(str, arg + i + 1, 1);
	else
		str = export_etc(arg + i + 1, *envp, str, info);
	if (pos == -1)
	{
		*envp = add_env(*envp, str);
	}
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
	char	*tmp;

	tmp = NULL;
	if (!cur->arg)
		set_export_print(cur, info->envp, info);
	else
	{
		i = -1;
		while (cur->arg[++i])
		{
			while (cur->arg[i] && cur->arg[i] != ' ')
				tmp = ft_charjoin(tmp, cur->arg[i++]);
			if (!tmp || (tmp[0] != '_' && !ft_isalnum(tmp[0])))//tmp 존재하지 않을떄??
			{
				info->code = 1;
				return (error_print("export", cur->arg, strerror(errno), info));
			}
			add_export(tmp, &info->envp, info);
			ft_free(&tmp);
		}
		
		// if (cur->arg[0] != '_' && !ft_isalnum(cur->arg[0])) //env 조건 확인
		// {
		// 	info->code = 1; //추추
		// 	// return (error_print("export", cur->arg, "not a valid identifier", info));
		// 	return (error_print("export", cur->arg, strerror(errno), info));
		// }
		// add_export(cur, &info->envp, info);
	}
	g_ret_number = 0;
	return (RET_TRUE);
}
