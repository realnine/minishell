# include "../minishell.h"

int	input_multiline(t_cmd *cmd)
{
	char *buf;

	// 멀티라인 입력 모드
	cmd->fd_in = open("tmp_redi_multiline", O_RDWR | O_CREAT, \
			S_IRWXU | S_IRWXG | S_IRWXO);
	if (cmd->fd_in < 0)
		return (error_print(cmd->redi_in_arg, strerror(errno), NULL, 1));
	cmd->input_file = ft_strdup("tmp_redi_multiline");
	while (1)
	{
		buf = readline("> ");
		if (ft_strcmp(buf, cmd->redi_in_arg) == 0)
			break ;
		ft_putstr_fd(buf, cmd->fd_in);
		ft_putstr_fd("\n", cmd->fd_in);
		free(buf);
	}
	free(buf);
	return (RET_TRUE);
}

int	redirect_in(t_cmd *cmd)
{
	if (ft_strcmp(cmd->redi_in, "<<") == 0)
	{
		if (input_multiline(cmd) == RET_FALSE)
			return (RET_FALSE);
	}
	else
	{
		cmd->fd_in = open(cmd->redi_in_arg, O_RDWR, \
				S_IRWXU | S_IRWXG | S_IRWXO);
		if (cmd->fd_in < 0)
			return (error_print(cmd->redi_in_arg, strerror(errno), NULL, 1));
	}
	return (RET_TRUE);
}

int	redirect_out(t_cmd *cmd)
{
	if (ft_strcmp(cmd->redi_out, ">>") == 0)
	{
		cmd->fd_out = open(cmd->redi_out_arg, O_RDWR | O_CREAT | O_APPEND, \
			S_IRWXU | S_IRWXG | S_IRWXO);
		if (cmd->fd_out < 0)
			return (error_print(cmd->redi_out_arg, strerror(errno), NULL, 1));
	}
	else
	{
		cmd->fd_out = open(cmd->redi_out_arg, O_RDWR | O_CREAT | O_TRUNC, \
			S_IRWXU | S_IRWXG | S_IRWXO);
		if (cmd->fd_out < 0)
			return (error_print(cmd->redi_out_arg, strerror(errno), NULL, 1));
	}
	return (RET_TRUE);
}

int	set_redi_io(t_info *info)
{
	t_cmd *cur;

	cur = info->cmd_head;
	while (cur)
	{
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

/*
int	open_err_exit(char *redi, char *arg)
{
	printf("in redi erro '%s'\n", redi);
	printf("	arg : [%s]\n", arg);
	err_print(strerror(errno), 1);
	return (RET_FALSE);
}
*/