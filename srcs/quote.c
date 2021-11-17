#include "../minishell.h"

char	*first_quote(char *p1)
{
	while (*p1)
	{
		if (*p1 == '\"' || *p1 == '\'')
			return (p1);
		p1++;
	}
	return (NULL);
}

char	*second_quote(char *p2, char c)
{
	while (*p2)
	{
		if (*p2 == c)
			return (p2);
		p2++;
	}
	return (NULL);
}

void	check_quote(t_info *info)
{
	char	*p1;
	char	*p2;

	p1 = info->line;
	while (1)
	{
		p1 = first_quote(p1);
		if (!p1)
			return ;
		p2 = second_quote(p1 + 1, *p1);
		if (!p2)
			error_exit("mini: quote multiline error\n", info);
		info->num_quote++;
		p1 = p2 + 1;
	}
}

void	cut_quote_buf(t_info *info)
{
	char	*p1;
	char	*p2;
	int		i;
	int		j;

	i = 0;
	p1 = info->line;
	while (i < info->num_quote)
	{
		p1 = first_quote(p1);
		p2 = second_quote(p1 + 1, *p1);
		info->quote_book[i] = (char *)calloc(p2 - p1, sizeof(char));
		j = 0;
		while (++p1 < p2)
		{
			info->quote_book[i][j++] = *p1;
			*p1 = '0';
		}
		i++;
		p1 = p2 + 1;
	}
}

void	parse_quote(t_info *info)
{
	// quote syntax check ( " '또는 ' " 인 경우,  " 또는 '만 있는 경우)
	// quote 갯수 측정 (info->num_quote에 저장)
	check_quote(info); 

	if (info->num_quote > 0)
	{
		// info->num_quote 개수에 맞게 info->quote_buf 2중 배열을 할당한다
		info->quote_book = (char **)malloc(sizeof(char *) * (info->num_quote + 1));
		if (!info->quote_book)
			error_exit("malloc error\n", info);
		info->quote_book[info->num_quote] = NULL;

		// qoute내용을 info->quote_buf 에 담는다
		cut_quote_buf(info);
	}
}