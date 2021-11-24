#include "../minishell.h"

int	syntax_check_pipe(char **token)
{
	int		i;
	char	*msg;

	msg = "mini: syntax error near unexpected token `|'";
	i = 0;
	while (token[i])
	{
		if (token[i][0] == '|')
		{
			if (i == 0)
				return (err_print(msg, 258));
			if (token[i + 1])
			{
				if (token[i + 1][0] == '|')
					return (err_print(msg, 258));
			}
			else
				err_print("mini: doesn't support pipe input", 258);
		}
		i++;
	}
	return (RET_TRUE);
}

int	syntax_check_redi(t_info *info, char **token)
{
	int		i;
	char	*msg;

	msg = "mini: syntax error near unexpected token";
	i = 0;
	while (token[i])
	{
		if (is_redi(info, token[i]) == RET_TRUE)
		{
			if (!token[i + 1])
				return (err_print(msg, 258));
			if (is_redi(info, token[i + 1]) == RET_TRUE)
				return (err_print(msg, 258));
		}
		i++;
	}
	return (RET_TRUE);
}

int	syntax_check_cmd(t_info *info, char **token)
{
	int		i;
	int		num;
	char	*msg;

	msg = "command not Found";
	i = 0;
	num = 0;
	while (token[i])
	{
		if (is_cmd(info, token[i]) == RET_TRUE || is_path(token[i]) == RET_TRUE
			|| is_redi(info, token[i]) == RET_TRUE)
		{
			while (token[++i])
			{
				if (token[i][0] == '|')
				{
					i++;
					break ;
				}
			}
		}
		else
			return (error_print(token[i], msg, NULL, 127));
	}
	return (RET_TRUE);
}

int	syntax_check(t_info *info)
{
	if (syntax_check_pipe(info->token) == RET_FALSE)
		return (RET_FALSE);
	if (syntax_check_redi(info, info->token) == RET_FALSE)
		return (RET_FALSE);
	if (syntax_check_cmd(info, info->token) == RET_FALSE)
		return (RET_FALSE);
	return (RET_TRUE);
}
