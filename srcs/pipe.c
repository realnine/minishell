# include "../minishell.h"

void	make_pipe_book(t_info *info)
{
	t_cmd *cur;
	int	n;
	int i;

	cur = info->cmd_head;
	n = 0;
	while (cur->next)
	{
		n++;
		cur = cur->next;
	}
	if (n > 0)
	{
		info->pipe_book = ft_malloc_int2(n + 1, info);
		i = 0;
		while (i < n)
		{
			info->pipe_book[i] = ft_malloc_int(2, info);
			if (pipe(info->pipe_book[i++]) < 0)       // 파이프 생성 
				error_exit("pipe error\n", info);
		}
		info->pipe_book[i] = NULL;
	}
}

void	make_all_pipe(t_info *info)
{
	t_cmd	*cur;
	int		i;
	//pid_t	pid;

	// 모든 파이프를 생성, (info->pipe_book)
	make_pipe_book(info);

	cur = info->cmd_head;
	i = 0;
    // cmd구조체에 파이프 정보 fd[2]를 세팅
	while (cur)
	{
		if (info->pipe_book)
			if (info->pipe_book[i])
				cur->pipe_fd = info->pipe_book[i++];
		cur = cur->next;
	}
	cur = info->cmd_head;
	while (cur)
	{
		if (cur->next)
			cur->fd_out = cur->pipe_fd[WRITE];
		if (cur->prev)
			cur->fd_in = cur->prev->pipe_fd[READ];
		cur = cur->next;
	}
}
