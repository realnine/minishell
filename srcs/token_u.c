# include "../minishell.h"

static void	replace_q(t_info *info, char *token)
{
	int	i;
	int	j;
	int	k;
	int	q;

	i = 0;
	j = 0;
	k = 0;
	while (token[i])
	{
		if (token[i] == '\"' || token[i] == '\'')
		{
			q = info->idx_q;
			while (info->quote_book[q][k])
				token[j++] = info->quote_book[q][k++];
			i += k;
			k = 0;
			info->idx_q += 1;
		}
		else
		{
			if (token[i] == '\\')
				token[j++] = token[i++];
			token[j++] = token[i++];
		}
	}
	token[j] = '\0';
}

void	replace_quote(t_info *info)
{
	int		i;

	i = 0;
	while (info->token[i])
	{
		replace_q(info, info->token[i]);
		i++;
	}
}

/*
void	insert(char *new, char *line, int *first, int *i)
{
	if (*line == '\'' || *line == '\"')
	{
		if ((*first) == 0)
		{
			new[(*i)++] = ' ';
			new[(*i)++] = *line;
			(*first) = 1;
		}
		else
		{
			new[(*i)++] = *line;
			new[(*i)++] = ' ';
			(*first) = 0;
		}
	}
	else
		new[(*i)++] = *line;
}

char *insert_space_quote(t_info *info)
{
	char *new;
	char *line;
	int first;
	int	i;

	line = info->line;
	i = ft_strlen(line) + 1 + ((info->num_quote) * 2);
	new = (char *)calloc(i, sizeof(char));
	if (!new)
		error_exit("malloc error\n", info);
	i = 0;
	first = 0;
	while(*line)
	{
		insert(new, line, &first, &i);
		line++;
	}
	new[i] = '\0';
	free(info->line);
	return (new);
}
*/