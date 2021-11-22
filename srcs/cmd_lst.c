# include "../minishell.h"

void	add_cmd_list(t_info *info, int start, int end)
{
	t_cmd	*new;
	t_cmd	*cur;
		
	new = creat_cmd_struct(info);
	new->token1 = start;     // info->token 인덱스 시작 넘버
	new->token2 = end - 1;   // info->token 인덱스 끝 넘버

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
		// 만약 마지막 토큰이 |로 끝난다면 
		// start 와 i는 같이 배열을 마지막 인덱스 NULL을 가리킨다
		// 토큰이 없는 cmd리스트가 있다면 입력모드로 전환해 커맨드(토큰)을 입력 받아야 한다
	
	set_cmd_lst(info);

	
	return (RET_TRUE);
}

