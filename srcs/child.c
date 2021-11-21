# include "../minishell.h"

void	exe_cmd(t_info *info, t_cmd *cur)
{
	if (ft_strncmp(cur->cmd, "cd", 2) == 0)
		ft_cd(info, cur);
	else if (ft_strncmp(cur->cmd, "echo", 4) == 0)
		ft_echo(info, cur);
	else if (ft_strncmp(cur->cmd, "env", 3) == 0)
		ft_env(info, cur);
	else if (ft_strncmp(cur->cmd, "exit", 4) == 0)
		ft_exit(info, cur);
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
	if (pid > 0) // 부모
	{
		cur->pid = pid;

		if (cur->pipe_fd)
			close(cur->prev->pipe_fd[WRITE]);
	}
	else if (pid == 0) // 자식 프로세스는 여기로
	{
		cur->pid = getpid();
		if (cur->fd_in != 0)
			close(cur->prev->pipe_fd[WRITE]); // 읽어올 파이프의 쓰기fd 부분을 닫아주어야 한다
		
		printf("--------run child(%d)--------\n", cur->pid);
		//g_ret_number = 127;
		exe_cmd(info, cur);
		child_exit(info, cur, 0);
	}
	else
		error_exit("fork error\n", info);
	
	// 부모는 여기 아래로 빠져나간다
}

int is_blt(t_cmd *cur)
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

void    make_child(t_info *info)
{
    t_cmd   *cur;
    pid_t   pid;
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
					// 여긴 자식 프로세스를 분기한 부모 프로세스의 시그널을 세팅 하는 것에 의미가 있다
					// 자식 프로세스는 execve()로 실행 로직이 교체될 때, 사라지고 시그널 세팅 정보도 사라짐
        	    create_child(info, cur);
        	    // printf("hey\n");
        	    pid = wait(NULL);
        	    // printf("abc\n");
        	    printf("--------child exit(%d)-------\n", pid);
				//waitpid(pid, &g_ret_number, WUNTRACED);
				//if (WIFEXITED(g_ret_number))
				//	g_ret_number = WEXITSTATUS(g_ret_number);
        	}
		}
        cur = cur->next;
    }
}