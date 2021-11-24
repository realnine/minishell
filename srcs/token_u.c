#include "../minishell.h"

void	replace_qq(t_info *info, char *token, int *i, int *j)
{
	int	k;
	int	q;

	k = 0;
	while (token[(*i)])
	{
		if (token[(*i)] == '\"' || token[(*i)] == '\'')
		{
			q = info->idx_q;
			while (info->quote_book[q][k])
				token[(*j)++] = info->quote_book[q][k++];
			(*i) += k;
			k = 0;
			info->idx_q += 1;
		}
		else
		{
			if (token[(*i)] == '\\')
				token[(*j)++] = token[(*i)++];
			token[(*j)++] = token[(*i)++];
		}
	}
	token[(*j)] = '\0';
}

void	replace_q(t_info *info, char *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	replace_qq(info, token, &i, &j);
}

void	replace_quote(t_info *info)
{
	int	i;

	i = 0;
	while (info->token[i])
	{
		replace_q(info, info->token[i]);
		i++;
	}
}

char	*str_cat(t_info *info, char *token, char *ptr)
{
	char	*new;
	char	*g_ret;
	int		len;

	g_ret = ft_itoa(g_ret_number);
	len = ft_strlen(token) - 2 + ft_strlen(g_ret);
	new = (char *)calloc(len + 1, sizeof(char));
	if (!new)
		error_exit("malloc error", info);
	*ptr++ = '\0';
	ptr++;
	ft_strlcat(new, token, ft_strlen(token) + 1);
	ft_strlcat(new, g_ret, ft_strlen(new) + ft_strlen(g_ret) + 1);
	ft_strlcat(new, ptr, ft_strlen(new) + ft_strlen(ptr) + 1);
	free(token);
	free(g_ret);
	return (new);
}

void	replace_g_ret(t_info *info)
{
	int		i;
	char	*ptr;

	if (!info->token)
		return ;
	i = 0;
	while (info->token[i])
	{
		ptr = info->token[i];
		while (*ptr)
		{
			if (ft_strncmp(ptr, "$?", 2) == 0)
			{
				info->token[i] = str_cat(info, info->token[i], ptr);
				ptr = info->token[i];
			}
			ptr++;
		}
		i++;
	}
}
