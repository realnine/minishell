# include "../minishell.h"

int	**ft_malloc_int2(int len, t_info *info)
{
	int **ret;

	ret = (int **)malloc(sizeof(int *) * len);
	if (!ret)
		error_exit("malloc err\n", info);
	return (ret);
}

int	*ft_malloc_int(int len, t_info *info)
{
	int *ret;

	ret = (int *)malloc(sizeof(int) * len);
	if (!ret)
		error_exit("malloc err\n", info);
	return (ret);
}

char	*strtrim_autofree(char *src, char *str, t_info *info)
{
	char *dst;

	dst = ft_strtrim(src, str);
	free(src);
	if (!dst)
		error_exit("ft_strtrim error\n", info);
	return (dst);
}

t_cmd	*creat_cmd_struct(t_info *info)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		error_exit("malloc error\n", info);
	cmd->token1 = 0;
	cmd->token2 = 0;

	cmd->cmd = NULL;
	cmd->opt = '\0';
	cmd->arg = NULL;
	cmd->arg_token = NULL;

	cmd->redi_in = NULL;
	cmd->redi_in_arg = NULL;
	cmd->input_file = NULL;

	cmd->redi_out = NULL;
	cmd->redi_out_arg = NULL;

	cmd->fd_in = 0;
	cmd->fd_out = 1;

	cmd->pipe_fd = NULL;
	cmd->pid = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

int	is_path(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i++] == '/')
			return (RET_TRUE);
	}
	return (RET_FALSE);
}

int	is_opt(char *token)
{
	int	i;

	i = 0;
	if (ft_strncmp(token, "-n", 2) == 0)
	{
		i = 2;
		while (token[i] == 'n')
			i++;
		if (token[i] == '\0')
			return (RET_TRUE);
	}
	return (RET_FALSE);
}

int	is_cmd(t_info *info, char *token)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ft_strncmp(token, "/bin/", 5) == 0)
			token += 5;
		else if (ft_strncmp(token, "/usr/bin/", 9) == 0)
			token += 9;
		else if (ft_strncmp(token, "/usr/local/bin/", 15) == 0)
			token += 15;
		i++;
	}
	i = 0;
	while (info->cmd_book[i])
	{
		if (ft_strcmp(token, info->cmd_book[i]) == 0)
			return (RET_TRUE);
		i++;
	}
	return (RET_FALSE);
}

int	is_redi(t_info *info, char *token)
{
	int	i;

	if (ft_strlen(token) == 0)
			return (RET_FALSE);
	i = 0;
	while (info->redi_book[i])
	{
		if (ft_strcmp(token, info->redi_book[i]) == 0)
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
