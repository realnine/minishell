#include "../minishell.h"

int	is_path(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i++] == '/')
			return (RET_TRUE);
	}
	return (RET_FALSE);
}

int	is_opt(char *token)
{
	int	i;

	i = 0;
	if (ft_strncmp(token, "-n", 2) == 0)
	{
		i = 2;
		while (token[i] == 'n')
			i++;
		if (token[i] == '\0')
			return (RET_TRUE);
	}
	return (RET_FALSE);
}

int	is_cmd(t_info *info, char *token)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ft_strncmp(token, "/bin/", 5) == 0)
			token += 5;
		else if (ft_strncmp(token, "/usr/bin/", 9) == 0)
			token += 9;
		else if (ft_strncmp(token, "/usr/local/bin/", 15) == 0)
			token += 15;
		i++;
	}
	i = 0;
	while (info->cmd_book[i])
	{
		if (ft_strcmp(token, info->cmd_book[i]) == 0)
			return (RET_TRUE);
		i++;
	}
	return (RET_FALSE);
}

int	is_redi(t_info *info, char *token)
{
	int	i;

	if (ft_strlen(token) == 0)
		return (RET_FALSE);
	i = 0;
	while (info->redi_book[i])
	{
		if (ft_strcmp(token, info->redi_book[i]) == 0)
			return (RET_TRUE);
		i++;
	}
	return (RET_FALSE);
}

int	is_arg(t_info *info, char *token)
{
	if (is_cmd(info, token) == RET_FALSE
		&& is_redi(info, token) == RET_FALSE && token[0] != '|')
		return (RET_TRUE);
	return (RET_FALSE);
}
