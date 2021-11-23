# include "../minishell.h"

void	pipe_free(int **pipe_book)
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

void	redi_free(t_info *info)
{
	t_cmd *cur;

	cur = info->cmd_head;
	while (cur)
	{
		if (cur->redi_in)
		{
			close(cur->fd_in);
			if (cur->input_file)
			{
				unlink(cur->input_file);
				free(cur->input_file);
				cur->input_file = NULL;
			}
		}
		if (cur->redi_out)
			close(cur->fd_out);
		cur = cur->next;
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
	info->num_quote = 0;
	info->idx_q = 0;
	two_dimen_str_free(info->token);
	info->token = NULL;

	two_dimen_str_free(info->quote_book);
	info->quote_book = NULL;

	redi_free(info);
	pipe_free(info->pipe_book);

	cur = info->cmd_head;
	while (cur)
	{
		ft_free(&cur->arg);

		free(cur->arg_token);
		cur->arg_token = NULL;

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