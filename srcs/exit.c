#include "../minishell.h"

void	error_exit(char *msg, t_info *info)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit_free(info);
	exit(1);
}

void	normal_exit(char *msg, t_info *info)
{
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
	exit_free(info);
	exit(0);
}

void	child_exit(t_info *info, t_cmd *cur, int ret)
{
	(void)cur;
	exit_free(info);
	exit(ret);
}
