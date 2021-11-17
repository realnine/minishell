# include "../../minishell.h"

int	ft_isspace(char c) //whitespace(공백)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void	exit_arg(t_info *info, t_cmd *cur, int *ret_num)
{
	int	i;

	i = 0;
	if (cur->arg[i] == '-')
		i++;
	while (cur->arg[i])
	{
		if (!ft_isdigit(cur->arg[i]))
		{
			info->code = 255;
			error_print("exit", cur->arg, "numeric argument required", info);
			exit(255);
		}
	}
	*ret_num = ft_atoi(cur->arg);
}

void	ft_exit(t_info *info, t_cmd *cur) //추추
{
	int	i;
	int	ret_num;

	i = -1;
	ret_num = 0;
	while (cur->arg[++i])
	{
		if (ft_isspace(cur->arg[i]))
			error_print("exit", "too many arguments", NULL, info);
	}
	exit_arg(info, cur, &ret_num);
	exit(ret_num);
}
