#include "../minishell.h"

char	*first_quote(char *p1)
{
	while (*p1)
	{
		if (*p1 == '\\' && (*(p1 + 1) == '\"' || *(p1 + 1) == '\''))
			p1 += 2;
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
		if (*p2 == '\\' && (*(p2 + 1) == '\"' || *(p2 + 1) == '\''))
			p2 += 2;
		if (*p2 == c)
			return (p2);
		p2++;
	}
	return (NULL);
}

int	check_quote(t_info *info)
{
	char	*p1;
	char	*p2;

	p1 = info->line;
	while (1)
	{
		p1 = first_quote(p1);
		if (!p1)
			return (RET_TRUE);
		p2 = second_quote(p1 + 1, *p1);
		if (!p2)
			return (err_print("mini: doesn't support quote multiline", 258));
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
		info->quote_book[i] = (char *)calloc(p2 - p1 + 2, sizeof(char));
		if (!info->quote_book[i])
			error_exit("malloc error", info);
		j = 0;
		while (p1 <= p2)
		{
			info->quote_book[i][j++] = *p1;
			if (*p1 != '\'' && *p1 != '\"')
				*p1 = '0';
			p1++;
		}
		i++;
	}
}

int	parse_quote(t_info *info)
{
	char	**tmp;

	if (check_quote(info) == RET_FALSE)
		return (RET_FALSE);
	if (info->num_quote > 0)
	{
		tmp = (char **)malloc(sizeof(char *) * (info->num_quote + 1));
		info->quote_book = tmp;
		if (!info->quote_book)
			error_exit("malloc error", info);
		info->quote_book[info->num_quote] = NULL;
		cut_quote_buf(info);
	}
	return (RET_TRUE);
}
