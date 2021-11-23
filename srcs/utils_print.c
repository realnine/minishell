# include "../minishell.h"

/* void	print_child(t_info *info)
{
	t_cmd *cur;

	cur = info->cmd_head;
	printf("created child : ");
	while (cur)
	{
		printf("[%d] ", cur->pid);
		cur = cur->next;
	}
	printf("\n\n");
} */

int		err_print(char *msg, int ret)
{
	g_ret_number = ret;
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (RET_FALSE);
}

void	print_pipe_book(t_info *info)
{
	int	i;
	int **book;

	i = -1;
	book = info->pipe_book;
	if (book)
	{
		printf("pipe : ");
		while(book[++i])
			printf("[w:%d, r:%d]  ",book[i][1], book[i][0]);
		printf("\n");
	}
}

void	print_quote(t_info *info)
{
	int i;

	i = 0;
	if (info->quote_book)
	{
		printf("quote_book : ");
		while (info->quote_book[i])
			printf("[%s] ", info->quote_book[i++]);
		printf("\n");
	}
}

void	print_token(char **token)
{
	int i;

	printf("token : ");
	if (!token)
	{
		printf("(null)\n");
		return ;
	}
	i = 0;
	while (token[i])
	{
		printf("[%s] ", token[i++]);
	}
	printf("\n");
}

// 리트스 내용 확인
void	print_cmd_lst(t_info *info)
{
	t_cmd	*cur;
	int		i;

	cur = info->cmd_head;
	while (cur)
	{
		printf("=======================\n");
		printf("	token1	: [%d]\n", cur->token1);
		printf("	token2	: [%d]\n", cur->token2);
		printf("	cmd	: [%s]\n", cur->cmd);
		printf("	opt	: [%c]\n", cur->opt);
		printf("	arg	: [%s]\n", cur->arg);
		printf("	redi_in		: [%s]\n", cur->redi_in);
		printf("	redi_in_arg	: [%s]\n", cur->redi_in_arg);
		printf("	redi_out	: [%s]\n", cur->redi_out);
		printf("	redi_out_arg	: [%s]\n", cur->redi_out_arg);
		printf("	fd_in	: (%d)\n", cur->fd_in);
		printf("	fd_out	: (%d)\n", cur->fd_out);
		//printf("	pipe	: (%p)\n", cur->pipe);
		i = 0;
		if (cur->arg_token)
		{
			printf("	arg_toekn : ");
			while (cur->arg_token[i])
				printf("[%s] ", cur->arg_token[i++]);
			printf("\n");
		}
		printf("=======================\n");
		//if (cur->prev)
		//	printf("	=> prev	: [%s]\n\n", cur->prev->full_str);
		//printf("	=> tokens	: ");
		//print_token(cur->token);
		cur = cur->next;
	}
}

// 해당 cmd리스트 내용확인
void	print_cmd(t_cmd *cur)
{
	printf("\n=======================\n");
	printf("token1	: [%d]\n", cur->token1);
	printf("token2	: [%d]\n", cur->token2);
	printf("cmd		: [%s]\n", cur->cmd);
	printf("opt		: [%c]\n", cur->opt);
	printf("arg		: [%s]\n", cur->arg);
	printf("fd_in	: (%d)\n", cur->fd_in);
	printf("fd_out	: (%d)\n", cur->fd_out);
	//printf("pipe	: (%p)\n", cur->pipe);
	printf("=======================\n");
}

int error_print(char *s1, char *s2, char *s3, int ret)
{
	g_ret_number = ret; //추추
	ft_putstr_fd("mini: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s2, 2);
	if (s3)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(s3, 2);
	}
	ft_putchar_fd('\n', 2);
	return (RET_FALSE);
}
