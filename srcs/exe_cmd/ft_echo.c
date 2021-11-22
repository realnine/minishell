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

char	*cut_env_name(char *arg, int *i, t_info *info)
{
	int	len;
	char	*res;

	len = 0;
	while (arg[len] && (ft_isalpha(arg[len]) || arg[len] == '_' || arg[len] == '?'))
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		error_exit("malloc error\n", info);
	ft_memcpy(res, arg, len);
	res[len] = '\0';
	*i += len - 1;
	return (res);
}
//echo $HOME eeee ERROR
void	ft_echo(t_info *info, t_cmd *cur) //echo -n (null) 처리 Test
{
	char	*env_val;
	char	*str;
	char	*name;
	int	i;

	i = -1;
	str = NULL;
	env_val = NULL;
	name = NULL;
	if (!cur->arg)
		str = ft_strdup("");
	else
	{
		while (cur->arg[++i])
		{
			if (cur->arg[i] == '$' && cur->arg[i + 1] && cur->arg[i + 1] != '\0')
			{
				i++;
				name = cut_env_name(cur->arg + i, &i, info);
				env_val = find_env_val(name, info->envp);
				if (!ft_strcmp("?", name))
					str = ft_strjoin_free(str, ft_itoa(g_ret_number), 3);
				else if (env_val)
					str = ft_strjoin_free(str, env_val, 1);
				ft_free(&name);
			}
			else
				str = ft_charjoin(str, cur->arg[i]);
		}
	}
	ft_putstr_fd(str, cur->fd_out);
	if (cur->opt != 'n')
		ft_putchar_fd('\n', cur->fd_out);
	ft_free(&str);
	g_ret_number = 0; //추추
}