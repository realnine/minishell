# include "../../minishell.h"
//env_name 조건 = !ft_strchr(" \t\n$\"\'\\/"
int	env_denied(t_info *info, char *arg)
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
			{
				info->code = 126;
				return (error_print("env", env_val, "Permission denied", info));
			}
		}
	}
	return (error_print("env", arg, "No such file or directory", info));
}

int	ft_env(t_info *info, t_cmd *cur)
{
	int	i;

	g_ret_number = 0; //추추
	if (cur->arg)
	{
		if (cur->arg[0] != '-')
			return (RET_TRUE);
		else
			return (env_denied(info, cur->arg));
	}
	i = -1;
	while (info->envp[++i])
	{
		ft_putstr_fd(info->envp[i], cur->fd_out);
		ft_putchar_fd('\n', cur->fd_out);
	}
	return (RET_TRUE);
}
