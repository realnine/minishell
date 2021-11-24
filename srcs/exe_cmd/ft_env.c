# include "../../minishell.h"
//env_name 조건 = !ft_strchr(" \t\n$\"\'\\/"
int	env_denied(t_info *info, t_cmd *cur, char *arg)
{
	int	i;
	char	*env_val;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '$')
		{
			i++;
			env_val = find_env_val(arg + i, info->envp);
			if (env_val != NULL)
				return (error_print("env", env_val, "Permission denied", 126));
			else
				return (print_env(info, cur));
		}
	}
	return (error_print("env", arg, "No such file or directory", 0)); //숫자
}

int	print_env(t_info *info, t_cmd *cur)
{
	int	i;
	int	j;
	char	*name;

	i = -1;
	while (info->envp[++i])
	{
		j = 0;
		name = cut_env_name(info->envp[i], &j);
		if (info->envp[i][j + 1] != '\0')
		{
			ft_putstr_fd(info->envp[i], cur->fd_out);
			ft_putchar_fd('\n', cur->fd_out);
		}
		ft_free(&name);
	}
	return (RET_TRUE);
}

int	ft_env(t_info *info, t_cmd *cur)
{
	g_ret_number = 0; //추추
	if (cur->arg_token)
	{
		if (cur->arg_token[0][0] != '-')
			return (env_denied(info, cur, cur->arg_token[0]));
		else
			return (RET_TRUE);
	}
	return (print_env(info, cur));
}
