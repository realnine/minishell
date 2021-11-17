# include "../../minishell.h"

void	ft_pwd(t_cmd *cur) //이래도 되나,,?
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	ft_putstr_fd(path, cur->fd_out);
	ft_putstr_fd("\n", cur->fd_out);
	g_ret_number = 0;
}
