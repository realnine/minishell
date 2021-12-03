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
		ft_free(&s1);
	else if (flag == 2)
		ft_free(&s2);
	else if (flag == 3)
	{
		ft_free(&s1);
		ft_free(&s2);
	}
	return (str);
}

void	remove_q(char *arg, char flag)
{
	int		i;
	int		len;

	len = ft_strlen(arg);
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == flag)
		{
			ft_strlcpy(arg + i, arg + i + 1, len - i);
			i--;
		}
	}
}
