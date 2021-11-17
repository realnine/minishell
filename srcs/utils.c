# include "../minishell.h"

char	*strtrim_autofree(char *src, char *str, t_info *info)
{
	char *dst;

	dst = ft_strtrim(src, str);
	free(src);
	//if (!dst)
	//	error_exit("ft_strtrim error\n", info);
	if (info)
		ft_putstr_fd("", 1); // tmp
	return (dst);
}

t_cmd	*creat_cmd_struct(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->token1 = 0;
	cmd->token2 = 0;

	cmd->cmd = NULL;
	cmd->opt = '\0';
	cmd->arg = NULL;

	cmd->redi_in = NULL;
	cmd->redi_out = NULL;
	cmd->redi_in_arg = NULL;
	cmd->redi_out_arg = NULL;

	cmd->fd_in = 0;
	cmd->fd_out = 1;

	cmd->pipe_fd = NULL;
	cmd->pid = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

int	is_cmd(t_info *info, char *token)
{
	int	i;
	int	len;

	i = 0;
	while (info->cmd_book[i])
	{
		len = ft_strlen(token);
		if (ft_strncmp(token, info->cmd_book[i], len) == 0)
			return (RET_TRUE);
		i++;
	}
	return (RET_FALSE);
}

int	is_redi(t_info *info, char *token)
{
	int	i;
	int	len;

	i = 0;
	while (info->redi_book[i])
	{
		len = ft_strlen(token);
		if (ft_strncmp(token, info->redi_book[i], len) == 0)
			return (RET_TRUE);
		i++;
	}
	return (RET_FALSE);
}

int	is_arg(t_info *info, char *token)
{
	if (is_cmd(info, token) == RET_FALSE &&
		is_redi(info, token) == RET_FALSE && token[0] != '|')
		return (RET_TRUE);
	return (RET_FALSE);
}

/* char	*cut_str(t_info *info, char *start, int len)
{
	char	*cut_str;

	if (len <= 0)
		return (NULL);
	cut_str = (char *)malloc(sizeof(char) * len + 1);
	if (!cut_str)
		error_exit("malloc error\n", info);
	ft_strlcpy(cut_str, start, len + 1);
	return (cut_str);
} */


/*
t_pipe	*create_pipe_struct(void)
{
	t_pipe *pipe;

	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	pipe->fd_in = -1;
	pipe->fd_out = -1;
	pipe->prev_cmd = NULL;
	pipe->next_cmd = NULL;
	return (pipe);
}
t_cmd	*get_tail_cmd(t_info *info)
{
	t_cmd *cur;

	cur = info->cmd_head;
	if (!cur)
		return (cur);
	while (cur->next)
		cur = cur->next;
	return (cur);
}
*/
