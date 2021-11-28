#include "../../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2, int flag)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
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

int	remove_q(char *arg, char flag)
{
	char	*ret;
	int	i;
	int	len;
	int	ck;

	len = ft_strlen(arg);
	ret = NULL;
	i = -1;
	ck = 2;
	while (arg[++i])
	{
		if (arg[i] == flag)
		{
			ft_strlcpy(arg + i, arg + i + 1, len - i);
			i--;
			ck++;
		}
	}
	return (ck / 2);
}

int		not_interpre(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	if (str[0] == '\'' && str[1] == '$' && str[len - 1] == '\'')
		return (RET_TRUE);
	return (RET_FALSE);
}

char	*set_echo(t_info *info, t_cmd *cur)
{
	int	i;
	int	j;
	char	*str;
	char	*name;
	char	*val;

	i = -1;
	str = NULL;
	while (cur->arg_token[++i])
	{
		if (not_interpre(cur->arg_token[i]))
		{
			remove_q(cur->arg_token[i], '\'');
			str = ft_strjoin_free(str, cur->arg_token[i], 1);
		}
		else
		{
			j = -1;
			while (cur->arg_token[i][++j])
			{
				if (cur->arg_token[i][j] == '$' && cur->arg_token[i][j + 1] \
				&& cur->arg_token[i][j + 1] != '\0')
				{
					j++;
					name = cut_env_name(cur->arg_token[i] + j, &j);
					val = find_env_val(name, info->envp);
					str = ft_strjoin_free(str, val, 1);
				}
				else if (cur->arg_token[i][j] && cur->arg_token[i][j] != '\"')
					str = ft_charjoin(str, cur->arg_token[i][j]);
			}
		}
		str = ft_charjoin(str, ' ');
	}
	return (str);
}

int	ft_echo(t_info *info, t_cmd *cur)
{
	char	*str;

	str = NULL;
	if (!cur->arg_token)
		str = ft_strdup("");
	else
		str = set_echo(info, cur);
	ft_putstr_fd(str, cur->fd_out);
	if (cur->opt != 'n')
		ft_putchar_fd('\n', cur->fd_out);
	//int i = -1;
	//while (cur->arg_token[++i])
	//	printf("token %d = [%s]\n", i, cur->arg_token[i]);
	//printf("\n");
	ft_free(&str);
	(void)info;
	g_ret_number = 0;
	return (RET_TRUE);
}
