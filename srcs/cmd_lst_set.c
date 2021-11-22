# include "../minishell.h"

void	set_cmd(t_info *info, t_cmd *cur)
{
	int		i;
	int		j;

	i = cur->token1;
	while (i <= cur->token2)
	{
		if (is_cmd(info, info->token[i]) == RET_TRUE)
		{
			cur->cmd = info->token[i];
			if (ft_strncmp(info->token[i + 1], "-n", 2) == 0)
			{
				j = 2;
				while (info->token[i + 1][j] == 'n')
					j++;
				if (info->token[i + 1][j] == '\0')
					cur->opt = 'n';
			}
			return ;
		}
		else if (is_redi(info, info->token[i]) == RET_TRUE)
			i += 2;
	}
}


void	set_redi(t_info *info, t_cmd *cur)
{
	int	i;

	i = cur->token1;
	while (info->token[i] && i <= cur->token2)
	{
		if (is_redi(info, info->token[i]) == RET_TRUE)
		{
			if (info->token[i][0] == '<')
			{
				cur->redi_in = info->token[i];
				cur->redi_in_arg = info->token[++i];
			}
			else
			{
				cur->redi_out = info->token[i];
				cur->redi_out_arg = info->token[++i];
			}
		}
		i++;
	}
}

char	**add_arg_token(char **arg_token, char *arg)
{
	char **new;
	int	i;

	new = (char **)malloc(sizeof(char *) * (ft_strslen(arg_token) + 2));
	if (!new)
		return (NULL);
	if (!arg_token)
	{
		new[0] = arg;
		new[1] = NULL;
	}
	else
	{
		i = -1;
		while (arg_token[++i])
			new[i] = arg_token[i];
		new[i] = arg;
		new[++i] = NULL;
		free(arg_token);
	}
	return (new);
}

void	put_arg(t_info *info, t_cmd *cur, int i)
{
	char	*tmp;

	if (!cur->arg)
		cur->arg = ft_strdup(info->token[i]);
	else
	{
		tmp = cur->arg;
		cur->arg = ft_strjoin2(cur->arg, " ", info->token[i]);
		free(tmp);
	}
	
	cur->arg_token = add_arg_token(cur->arg_token, info->token[i]);
	if (!cur->arg_token)
		error_exit("malloc error\n", info);
	
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
			if (cur->opt == 'n')
				i += 1; // opt 토큰도 건너 뛰도록
		}
		else if (is_redi(info, info->token[i]) == RET_TRUE)
			i += 1; // redi_arg 토큰도 건너 뛰도록
		else
			put_arg(info, cur, i);
		i++;
	}
	
}

void	set_cmd_lst(t_info *info)
{
	t_cmd	*cur;

	cur = info->cmd_head;
	while (cur)
	{
		set_cmd(info, cur);
		set_redi(info, cur);
		set_arg(info, cur);
		cur = cur->next;
	}
}
