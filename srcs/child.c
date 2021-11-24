#include "../minishell.h"

void	exe_cmd(t_info *info, t_cmd *cur)
{
	if (ft_strncmp(cur->cmd, "cd", 2) == 0)
		ft_cd(info, cur);
	else if (ft_strncmp(cur->cmd, "echo", 4) == 0)
		ft_echo(info, cur);
	else if (ft_strncmp(cur->cmd, "env", 3) == 0)
		ft_env(info, cur);
	else if (ft_strncmp(cur->cmd, "exit", 4) == 0)
		ft_exit(cur);
	else if (ft_strncmp(cur->cmd, "export", 6) == 0)
		ft_export(info, cur);
	else if (ft_strncmp(cur->cmd, "pwd", 3) == 0)
		ft_pwd(cur);
	else if (ft_strncmp(cur->cmd, "unset", 5) == 0)
		ft_unset(info, cur);
	else
		ft_execve(info, cur);
}

void	create_child(t_info *info, t_cmd *cur)
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
	{
		cur->pid = pid;
		if (cur->prev)
			close(cur->prev->pipe_fd[WRITE]);
	}
	else if (pid == 0)
	{
		cur->pid = getpid();
		if (cur->prev)
			close(cur->prev->pipe_fd[WRITE]);
		exe_cmd(info, cur);
		child_exit(info, cur, 0);
	}
	else
		error_exit("fork error\n", info);
}

int	is_blt(t_cmd *cur)
{
	if (ft_strncmp(cur->cmd, "cd", 2) == 0)
		return (RET_TRUE);
	else if (ft_strncmp(cur->cmd, "echo", 4) == 0)
		return (RET_TRUE);
	else if (ft_strncmp(cur->cmd, "env", 3) == 0)
		return (RET_TRUE);
	else if (ft_strncmp(cur->cmd, "exit", 4) == 0)
		return (RET_TRUE);
	else if (ft_strncmp(cur->cmd, "export", 6) == 0)
		return (RET_TRUE);
	else if (ft_strncmp(cur->cmd, "pwd", 3) == 0)
		return (RET_TRUE);
	else if (ft_strncmp(cur->cmd, "unset", 5) == 0)
		return (RET_TRUE);
	else
		return (RET_FALSE);
}

void	make_child(t_info *info)
{
	t_cmd	*cur;
	pid_t	pid;
	int		stat;

	cur = info->cmd_head;
	while (cur)
	{
		if (cur->cmd)
		{
			if (is_blt(cur))
				exe_cmd(info, cur);
			else
			{
				set_signal(2);
				create_child(info, cur);
				pid = wait(&stat);
				g_ret_number = stat / 256;
			}
		}
		cur = cur->next;
	}
}
