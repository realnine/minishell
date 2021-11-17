# include "../minishell.h"

void	syntax_check_pipe(t_info *info, char **token)
{
	int		i;
	char	msg[] = "mini: syntax error near unexpected token `|'\n";

	i = 0;
	while (token[i])
	{
		if (token[i][0] == '|')
		{
			if (i == 0)
				error_exit(msg, info);
			if (token[i + 1])
			{
				if (token[i + 1][0] == '|')
					error_exit(msg, info);
			}
			else
				error_exit("mini: pipe multiline error\n", info);
		}
		i++;
	}
}

void	syntax_check_redi(t_info *info, char **token)
{
	int		i;
	char	msg[] = "mini: syntax error near unexpected token `newline'\n";

	i = 0;
	while (token[i])
	{
		if (is_redi(info, token[i]) == RET_TRUE)
		{
			if (!token[i + 1])
				error_exit(msg, info);
			if (is_redi(info, token[i + 1]) == RET_TRUE)
				error_exit(msg, info);
		}
		i++;
	}
}

void	syntax_check_cmd(t_info *info, char **token)
{
	int		i;
	int		num;
	char	msg[] = "mini: command not found 1\n";

	i = 0;
	num = 0;
	while (1)
	{
		if (token[i] == NULL)
		{
			if (num == 0)
				error_exit(msg, info);
			return ;
		}	
		else if (token[i][0] == '|')
		{
			if (num == 0)
				error_exit(msg, info);
			else
				num = 1;
		}
		else if (is_cmd(info, token[i]) == RET_TRUE ||
				is_redi(info, token[i]) == RET_TRUE)
			num = 1;
		i++;
	}
}

void	syntax_check_arg(t_info *info, char **token)
{
	int		i;
	int		num;
	char	msg[] = "mini: command not found 2\n";

	i = 0;
	num = 0;
	while (token[i])
	{
		if (is_arg(info, token[i]) == RET_TRUE)
		{
			if (num == 0)
				error_exit(msg, info);
		}
		else if (is_cmd(info, token[i]) == RET_TRUE ||
				is_redi(info, token[i]) == RET_TRUE)
			num = 1;
		else if (token[i][0] == '|')
			num = 0;
		i++;
	}
}

void	syntax_check(t_info *info)
{
	syntax_check_pipe(info, info->token);
		// 파이프 좌항 인자가 있는지, 파이프가 연속으로 두번 나왔는지 체크
		// 우항 인자가 없을 땐, 입력모드로 들어간다
	syntax_check_redi(info, info->token); 
		// 리다이렉트가 두번 연속으로 나왔는지 체크
		// 리다리렉트 인자가 있는지 체크
	syntax_check_cmd(info, info->token); 
		// 한 라인에(또는 파이프 사이에) 커맨드가 있는지 체크
	syntax_check_arg(info, info->token); 
		// 인자가 커맨드 이전에 나오는지 체크
}

