#include "../minishell.h"

void	set_cmd(t_info *info, t_cmd *cur)
{
	int		i;

	i = cur->token1;
	while (i <= cur->token2)
	{
		if (is_cmd(info, info->token[i]) == RET_TRUE
			|| is_path(info->token[i]) == RET_TRUE)
		{
			cur->cmd = info->token[i];
			if (is_opt(info->token[i + 1]) == RET_TRUE)
				cur->opt = 'n';
			return ;
		}
		else if (is_redi(info, info->token[i]) == RET_TRUE)
			i += 2;
	}
}

int	set_redi2(t_info *info, t_cmd *cur, int *i)
{
	if (info->token[(*i)][0] == '<')
	{
		if (cur->fd_in != 0)
			close(cur->fd_in);
		if (cur->input_file)
		{
			unlink(cur->input_file);
			free(cur->input_file);
			cur->input_file = NULL;
		}
		cur->redi_in = info->token[(*i)];
		cur->redi_in_arg = info->token[++(*i)];
		if (redirect_in(cur) == RET_FALSE)
			return (RET_FALSE);
	}
	else
	{
		if (cur->fd_out != 1)
			close(cur->fd_out);
		cur->redi_out = info->token[(*i)];
		cur->redi_out_arg = info->token[++(*i)];
		if (redirect_out(cur) == RET_FALSE)
			return (RET_FALSE);
	}
	return (RET_TRUE);
}

int	set_redi(t_info *info, t_cmd *cur)
{
	int	i;

	i = cur->token1;
	while (info->token[i] && i <= cur->token2)
	{
		if (is_redi(info, info->token[i]) == RET_TRUE)
		{
			if (set_redi2(info, cur, &i) == RET_FALSE)
				return (RET_FALSE);
		}
		i++;
	}
	return (RET_TRUE);
}

void	set_arg(t_info *info, t_cmd *cur)
{
	int		i;
	int		cmd;

	cmd = 0;
	i = cur->token1;
	while (info->token[i] && i <= cur->token2)
	{
		if (is_cmd(info, info->token[i]) == RET_TRUE && cmd == 0)
		{
			cmd = 1;
			i++;
			while (is_opt(info->token[i]) == RET_TRUE)
				i++;
		}
		else if (is_redi(info, info->token[i]) == RET_TRUE)
			i += 2;
		else
			put_arg(info, cur, i++);
	}
}
