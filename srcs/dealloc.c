# include "../minishell.h"

void	pipe_free_fd_close(int **pipe_book)
{
	int i;

	i = 0;
	if (pipe_book)
	{
		while (pipe_book[i])
		{
			close(pipe_book[i][0]);
			close(pipe_book[i][1]);
			free(pipe_book[i]);
			i++;
		}
		free(pipe_book);
	}
}

void	redi_fd_close(t_info *info)
{
	t_cmd *cur;

	cur = info->cmd_head;
	while (cur)
	{
		if (cur->redi_in)
		{
			close(cur->fd_in);
			//if (ft_stdcmp(cur->redi_in, "<<") == 0)
			//	unlink(cur->redi_in_arg);
		}
		if (cur->redi_out)
			close(cur->fd_out);
	}
}

void	two_dimen_str_free(char	**buf)
{
	int	i;

	if (!buf)
		return ;
	i = 0;
	while (buf[i])
	{
		free(buf[i++]);
	}
	free(buf);
}

void	ft_free(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

void	reset_free(t_info *info)
{
	t_cmd	*cur;
	t_cmd	*tmp;

	ft_free(&info->line);

	two_dimen_str_free(info->token);
	info->token = NULL;
	two_dimen_str_free(info->quote_book);
	info->quote_book = NULL;
	//pipe_free(info->pipe_book);
	// redi_free(info)
	cur = info->cmd_head;
	while (cur)
	{
		ft_free(&cur->arg);
		if (cur->redi_in > 0)
			close(cur->fd_in);
		if (cur->redi_out > 0)
			close(cur->fd_out);

		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
	info->cmd_head = NULL;
}

void	exit_free(t_info *info)
{
	int	i;

	reset_free(info);
	two_dimen_str_free(info->envp);
	if (info->cmd_book)
	{
		i = 0;
		while (info->cmd_book[i])
		{
			free(info->cmd_book[i++]);
		}
	}
	if (info->redi_book)
	{
		i = 0;
		while (info->redi_book[i])
		{
			free(info->redi_book[i++]);
		}
	}
}