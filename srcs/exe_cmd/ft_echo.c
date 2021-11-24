# include "../../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2, int flag)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	if (s1)
		ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len);
	str[s1_len + s2_len] = '\0';
	if (flag == 1)
		free(s1);
	else if (flag == 2)
		free(s2);
	else if (flag == 3)
	{
		free(s1);
		free(s2);
	}
	return (str);
}

char	*cut_env_name(char *arg, int *i)
{
	int	len;
	char	*res;

	len = 0;
	while (arg[len] && (ft_isalpha(arg[len]) || arg[len] == '_' || arg[len] == '?'))
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		error_print("malloc error", NULL, NULL, 0); //malloc error g_ret_number 값찾기
	ft_memcpy(res, arg, len);
	res[len] = '\0';
	*i += len - 1;
	return (res);
}

char	*set_echo(t_info *info, char **token)
{
	char	*ret;
	char	*name;
	char	*env_val;
	int	i;
	int	j;

	i = -1;
	ret = NULL;
	while (token[++i])
	{
		j = -1;
		while (token[i][++j])
		{
			if (token[i][j] == '$' && token[i][j + 1] && token[i][j + 1] != '\0')
			{
				j++;
				name = cut_env_name(token[i] + j, &j);
				env_val = find_env_val(name, info->envp);
				if (!ft_strcmp("?", name))
					ret = ft_strjoin_free(ret, ft_itoa(g_ret_number), 3);
				else if (env_val)
					ret = ft_strjoin_free(ret, env_val, 1);
				ft_free(&name);
			}
			else
				ret = ft_charjoin(ret, token[i][j]);
		}
		if (token[i + 1] != NULL)
			ret = ft_charjoin(ret, ' ');
	}
	return (ret);
}

int	ft_echo(t_info *info, t_cmd *cur)// (0)
{
	char	*str;

	str = NULL;
	if (!cur->arg_token) //될까?
		str = ft_strdup("");
	else
		str = set_echo(info, cur->arg_token);
	ft_putstr_fd(str, cur->fd_out);
	if (cur->opt != 'n')
		ft_putchar_fd('\n', cur->fd_out);
	ft_free(&str);
	g_ret_number = 0; //추추
	return (RET_TRUE);
}