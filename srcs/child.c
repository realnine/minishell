# include "../minishell.h"

void	exe_cmd(t_info *info, t_cmd *cur)
{
	//if (ft_strncmp(cur->cmd, "cd", 2) == 0)
	//	ft_cd(info, cur);
	//else if (ft_strncmp(cur->cmd, "echo", 4) == 0)
	//	ft_echo(info, cur);
	//else if (ft_strncmp(cur->cmd, "env", 3) == 0)
	//	ft_env(info, cur);
	//else if (ft_strncmp(cur->cmd, "exit", 4) == 0)
	//	ft_exit(info, cur);
	//else if (ft_strncmp(cur->cmd, "export", 6) == 0)
	//	ft_export(info, cur);
	//else if (ft_strncmp(cur->cmd, "pwd", 3) == 0)
	//	ft_pwd(cur);
	//else if (ft_strncmp(cur->cmd, "unset", 5) == 0)
	//	ft_unset(info, cur);
	//else
		ft_execve(info, cur);
}

void	set_child_io(t_info *info, t_cmd *cur)
{
	if (cur->next)
		cur->fd_out = cur->pipe_fd[WRITE];
	if (cur->prev)
		cur->fd_in = cur->prev->pipe_fd[READ];

	if (cur->redi_in)
		redirect_in(info, cur);
	if (cur->redi_out)
		redirect_out(info, cur);
}

void	create_child(t_info *info, t_cmd *cur)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0) // 자식 프로세스는 여기로
	{
		cur->pid = getpid();
		printf("--------run child(%d)--------\n", cur->pid);
		exe_cmd(info, cur);
		child_exit(info, cur, 0);
	}
	else if (pid > 0)
		cur->pid = pid;
	else
		error_exit("fork error\n", info);
	
	
	// 부모는 여기 아래로 빠져나간다
}

void	make_child(t_info *info)
{
	t_cmd	*cur;
	pid_t	pid;

	cur = info->cmd_head;
	while (cur)
	{
		set_child_io(info, cur);
		// 파이프가 있다면 info->pipe_book 메모리도 복제
		create_child(info, cur);
		pid = wait(NULL);
		printf("--------child exit(%d)-------\n", pid);
		cur = cur->next;
	}

}