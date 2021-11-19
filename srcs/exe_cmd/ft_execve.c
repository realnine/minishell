# include "../../minishell.h"
void	print_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		ft_putstr_fd("argv[", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd("] : ", 1);
		ft_putstr_fd(argv[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	ft_putstr_fd("------------------\n", 1);
}

char	**make_argv(t_info *info, t_cmd *cur)
{
	int		len;
	char	**argv;
	int		i;
	int		j;

	len = cur->token2 - cur->token1 + 1;
	argv = (char **)malloc(sizeof(char *) * (len + 1));
	if (!argv)
		error_exit("malloc error\n", info);
	i = 0;
	j = cur->token1;
	while (i < len)
	{
		argv[i] = info->token[j++];
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

char	**make_path(t_info *info)
{
	char	**path;

	path = (char **)malloc(sizeof(char *) * 4);
	if (!path)
		error_exit("malloc error\n", info);
	path[0] = ft_strdup("/bin/");
	if (!path[0])
		error_exit("malloc error\n", info);
	path[1] = ft_strdup("/usr/bin/");
	if (!path[1])
		error_exit("malloc error\n", info);
	path[2] = ft_strdup("/usr/local/bin");
	if (!path[2])
		error_exit("malloc error\n", info);
	path[3] = NULL;
	return (path);
}

void	free_path(char **path)
{
	free(path[0]);
	free(path[1]);
	free(path[2]);
	free(path);
}

void	ft_execve(t_info *info, t_cmd *cur)
{
	char	**argv;
	char	**path;
	int		i;

	path = make_path(info);
	argv = make_argv(info, cur);
	//set_signal(2);
	
	if (cur->fd_in != 0)
	{
		dup2(cur->fd_in, STDIN_FILENO);
		//close(cur->fd_in);
	}
	if (cur->fd_in != 1)
	{
		dup2(cur->fd_out, STDOUT_FILENO);
		//close(cur->fd_out);
	}

	i = 0;
	while (i < 3)
	{
		argv[0] = ft_strjoin(path[i], cur->cmd);
		//print_argv(argv);
		g_ret_number = execve(argv[0], argv, info->envp);
		// execve가 성공하면 아래부터는 실행되지 않음
		// execve가 성공하면 모든 메모리는 자동 해제됨
		ft_putstr_fd("-----execve 통과-----\n", 1);
		free (argv[0]); // strjoin
		i++;
	}
	free_path(path);
	free(argv);
	//exit(g_ret_number);
	error_exit("execve error\n", info);
}
