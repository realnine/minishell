#include "../minishell.h"

void	print_pipe_book(t_info *info)
{
	int	i;
	int	**book;

	i = -1;
	book = info->pipe_book;
	if (book)
	{
		printf("pipe : ");
		while (book[++i])
			printf("[w:%d, r:%d]  ", book[i][1], book[i][0]);
		printf("\n");
	}
}

void	print_quote(t_info *info)
{
	int	i;

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
	int	i;

	printf("token : ");
	if (!token)
	{
		printf("(null)\n");
		return ;
	}
	i = 0;
	while (token[i])
		printf("[%s] ", token[i++]);
	printf("\n");
}

void	print_cmd_lst(t_info *info)
{
	t_cmd	*cur;

	cur = info->cmd_head;
	while (cur)
	{
		printf("=======================\n");
		printf("	cmd	: [%s]\n", cur->cmd);
		printf("	opt	: [%c]\n", cur->opt);
		printf("	arg	: [%s]\n", cur->arg);
		printf("	redi_in		: [%s]\n", cur->redi_in);
		printf("	redi_in_arg	: [%s]\n", cur->redi_in_arg);
		printf("	redi_out	: [%s]\n", cur->redi_out);
		printf("	redi_out_arg	: [%s]\n", cur->redi_out_arg);
		printf("	fd_in	: (%d)\n", cur->fd_in);
		printf("	fd_out	: (%d)\n	", cur->fd_out);
		print_token(cur->arg_token);
		printf("=======================\n");
		cur = cur->next;
	}
}
