#include "../../minishell.h"

char	**make_argv(t_info *info, t_cmd *cur)
{
	char	**argv;
	int		i;

	argv = (char **)malloc(sizeof(char *) * (ft_strslen(cur->arg_token) + 2));
	if (!argv)
		error_exit("malloc error\n", info);
	argv[0] = cur->cmd;
	if (cur->arg_token)
	{
		i = -1;
		while (cur->arg_token[++i])
			argv[i + 1] = cur->arg_token[i];
		argv[i + 1] = NULL;
	}
	else
		argv[1] = NULL;
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

	argv = make_argv(info, cur);
	dup2(cur->fd_in, STDIN_FILENO);
	dup2(cur->fd_out, STDOUT_FILENO);
	if (is_path(cur->cmd) == RET_TRUE)
		g_ret_number = execve(argv[0], argv, info->envp);
	else
	{
		path = make_path(info);
		i = 0;
		while (i < 3)
		{
			argv[0] = ft_strjoin(path[i], cur->cmd);
			g_ret_number = execve(argv[0], argv, info->envp);
			free (argv[0]);
			i++;
		}
		free_path(path);
	}
	free(argv);
	exit_execve(info, cur);
}
