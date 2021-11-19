# include "../minishell.h"
int	open_err_exit(char *redi, char *arg)
{
	printf("in redi erro '%s'\n", redi);
	printf("	arg : [%s]\n", arg);
	err_print(strerror(errno));
	printf("\n");
	return (RET_FALSE);
}

int	redirect_in(t_cmd *cmd)
{
	char *buf;

	if (ft_strcmp(cmd->redi_in, "<<") == 0)
	{
		// 멀티라인 입력 모드
		cmd->fd_in = open("tmp_redi_multiline", O_RDWR | O_CREAT | O_APPEND, \
				S_IRWXU | S_IRWXG | S_IRWXO);
		if (cmd->fd_in < 0)
			return (open_err_exit("<<", cmd->redi_in_arg));
		while (1)
		{
			buf = readline("> ");
			if (ft_strcmp(buf, cmd->redi_in_arg) == 0)
				break ;
			ft_putstr_fd(buf, cmd->fd_in);
			ft_putstr_fd("\n", cmd->fd_in);
		}
	}
	else
	{
		cmd->fd_in = open(cmd->redi_in_arg, O_RDWR, \
				S_IRWXU | S_IRWXG | S_IRWXO);
		if (cmd->fd_in < 0)
			return (open_err_exit("<", cmd->redi_in_arg));
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
			open_err_exit(">>", cmd->redi_out_arg);
	}
	else
	{
		cmd->fd_out = open(cmd->redi_out_arg, O_RDWR | O_CREAT | O_TRUNC, \
			S_IRWXU | S_IRWXG | S_IRWXO);
		if (cmd->fd_out < 0)
			open_err_exit(">", cmd->redi_out_arg);
	}
	return (RET_TRUE);
}