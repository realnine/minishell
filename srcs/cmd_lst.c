# include "../minishell.h"

int	set_cmd_io(t_info *info)
{
	t_cmd *cur;

	cur = info->cmd_head;
	while (cur)
	{
		if (cur->next)
			cur->fd_out = cur->pipe_fd[WRITE];
		if (cur->prev)
			cur->fd_in = cur->prev->pipe_fd[READ];

		if (cur->redi_in)
			if (redirect_in(cur) == RET_FALSE)
				return (RET_FALSE);
		if (cur->redi_out)
			if (redirect_out(cur) == RET_FALSE)
				return (RET_FALSE);
		cur = cur->next;
	}
	return (RET_TRUE);
}

void	add_cmd_list(t_info *info, int start, int end)
{
	t_cmd	*new;
	t_cmd	*cur;
		
	new = creat_cmd_struct(info);
	new->token1 = start;     // info->token 인덱스 시작 넘버
	new->token2 = end - 1;   // info->token 인덱스 끝 넘버

	if (!info->cmd_head)
		info->cmd_head = new;
	else
	{
		cur = info->cmd_head;
		while (cur->next)
			cur = cur->next;
		new->prev = cur;
		cur->next = new;
	}
}

int	make_cmd_lst(t_info *info, char **token)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	while (token[i])
	{
		if (token[i][0] == '|')
		{
			add_cmd_list(info, start, i);
			start = ++i;
		}
		else
			i++;
	}
	add_cmd_list(info, start, i);   
		// 만약 마지막 토큰이 |로 끝난다면 
		// start 와 i는 같이 배열을 마지막 인덱스 NULL을 가리킨다
		// 토큰이 없는 cmd리스트가 있다면 입력모드로 전환해 커맨드(토큰)을 입력 받아야 한다
	
	set_cmd_lst(info);

	if (set_cmd_io(info) == RET_FALSE)
		return (RET_FALSE);
	return (RET_TRUE);
}

