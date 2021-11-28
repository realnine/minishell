#include "../minishell.h"

int	input_multiline(t_cmd *cmd)
{
	char	*buf;
	int		flags;
	int		fd;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open("tmp_redi_multiline", flags, 0777);
	if (cmd->fd_in < 0)
		return (err_print(strerror(errno), 1));
	cmd->input_file = ft_strdup("tmp_redi_multiline");
	while (1)
	{
		buf = readline("> ");
		if (ft_strcmp(buf, cmd->redi_in_arg) == 0)
			break ;
		ft_putstr_fd(buf, fd);
		ft_putstr_fd("\n", fd);
		free(buf);
	}
	free(buf);
	close(fd);
	return (RET_TRUE);
}

int	redirect_in(t_cmd *cmd)
{
	if (ft_strcmp(cmd->redi_in, "<<") == 0)
	{
		if (input_multiline(cmd) == RET_FALSE)
			return (RET_FALSE);
		cmd->fd_in = open(cmd->input_file, O_RDWR | O_CREAT, 0777);
	}
	else
	{
		cmd->fd_in = open(cmd->redi_in_arg, O_RDWR, 0777);
		if (cmd->fd_in < 0)
			return (error_print(cmd->redi_in_arg, strerror(errno), NULL, 1));
	}
	return (RET_TRUE);
}

int	redirect_out(t_cmd *cmd)
{
	int		flags;

	if (ft_strcmp(cmd->redi_out, ">>") == 0)
	{
		flags = O_RDWR | O_CREAT | O_APPEND;
		cmd->fd_out = open(cmd->redi_out_arg, flags, 0777);
		if (cmd->fd_out < 0)
			return (error_print(cmd->redi_out_arg, strerror(errno), NULL, 1));
	}
	else
	{
		flags = O_RDWR | O_CREAT | O_TRUNC;
		cmd->fd_out = open(cmd->redi_out_arg, flags, 0777);
		if (cmd->fd_out < 0)
			return (error_print(cmd->redi_out_arg, strerror(errno), NULL, 1));
	}
	return (RET_TRUE);
}

int	set_redi_io(t_info *info)
{
	t_cmd	*cur;

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
