#include "../minishell.h"

int	err_print(char *msg, int ret)
{
	g_ret_number = ret;
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (RET_FALSE);
}

int	error_print(char *s1, char *s2, char *s3, int ret)
{
	g_ret_number = ret;
	ft_putstr_fd("mini: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s2, 2);
	if (s3)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(s3, 2);
	}
	ft_putchar_fd('\n', 2);
	return (RET_FALSE);
}
