#include "../minishell.h"

void	add_cmd_list(t_info *info, int start, int end)
{
	t_cmd	*new;
	t_cmd	*cur;

	new = creat_cmd_struct(info);
	new->token1 = start;
	new->token2 = end - 1;
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

int	set_cmd_lst(t_info *info)
{
	t_cmd	*cur;

	cur = info->cmd_head;
	while (cur)
	{
		set_cmd(info, cur);
		if (set_redi(info, cur) == RET_FALSE)
			return (RET_FALSE);
		set_arg(info, cur);
		cur = cur->next;
	}
	return (RET_TRUE);
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
	if (set_cmd_lst(info) == RET_FALSE)
		return (RET_FALSE);
	return (RET_TRUE);
}
