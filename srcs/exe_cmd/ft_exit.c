#include "../../minishell.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	exit_arg(t_cmd *cur)
{
	int	i;
	int	ret;
	int	flag;

	i = 0;
	ret = 0;
	flag = 0;
	if (cur->arg_token[0][i] == '-')
	{
		flag = 1;
		i++;
	}
	while (cur->arg_token[0][i])
	{
		if (!ft_isdigit(cur->arg_token[0][i]))
		{
			error_print("exit", cur->arg, "numeric argument required", 255);
			exit(255);
		}
		i++;
	}
	ret = ft_atoi(cur->arg_token[0]);
	while (ret >= 256)
		ret = ret % 256;
	return (ret);
}

int	ft_exit(t_cmd *cur)
{
	int	i;
	int	ret;
	int	flag;

	i = -1;
	ret = 0;
	flag = 0;
	if (cur->arg_token)
	{
		while (cur->arg_token[++i])
		{
			flag++;
			if (flag == 2)
				return (error_print("exit", "too many arguments", NULL, 1));
			ret = exit_arg(cur);
		}
	}
	g_ret_number = ret;
	exit(ret);
	return (RET_TRUE);
}
