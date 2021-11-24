# include "../../minishell.h"

int	ft_isspace(char c) //whitespace(공백)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	exit_arg(t_cmd *cur)
{
	int	i;

	i = 0;
	if (cur->arg[i] == '-')
		i++;
	while (cur->arg[i])
	{
		if (!ft_isdigit(cur->arg[i]))
		{
			error_print("exit", cur->arg, "numeric argument required", 255);
			exit(255);
		}
		i++;
	}
	return (ft_atoi(cur->arg));
}

// void	ft_exit(t_info *info, t_cmd *cur) //추추
// {
// 	int	i;
// 	int	ret_num;

// 	i = -1;
// 	ret_num = 0;
// 	if (cur->arg)
// 	{
// 		while (cur->arg[++i])
// 		{
// 			if (ft_isspace(cur->arg[i]))
// 				error_print("exit", "too many arguments", NULL, 1);
// 		}
// 		exit_arg(info, cur, &ret_num);
// 	}
// 	exit(ret_num);
// }

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