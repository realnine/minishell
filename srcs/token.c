#include "../minishell.h"

int	get_sep_num(char *src, char *sep)
{
	int	num;
	int	sep_len;

	num = 0;
	sep_len = ft_strlen(sep);
	while (*src)
	{
		if (ft_strncmp(src, sep, sep_len) == 0)
		{
			if (sep_len == 1 && *(src + 1) == *sep && *sep != '|')
				src += 2;
			else
			{
				num++;
				src += sep_len;
			}
		}
		src++;
	}
	return (num);
}

void	insert_new_sep(char *dst, char *src, char *sep, char *new_sep)
{
	int	sep_len;

	sep_len = ft_strlen(sep);
	while (*src)
	{
		if (ft_strncmp(src, sep, sep_len) == 0)
		{
			if (sep_len == 1 && *(src + 1) == *sep && *sep != '|')
			{
				ft_memcpy(dst, src, 2);
				dst += 2;
				src += 2;
			}
			else
			{
				ft_memcpy(dst, new_sep, sep_len + 2);
				dst += sep_len + 2;
				src += sep_len;
			}
		}
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
}

char	*insert_space(char *src, char *sep, t_info *info)
{
	char	*new_sep;
	int		num;
	char	*dst;

	num = get_sep_num(src, sep);
	if (num == 0)
		return (src);
	dst = (char *)malloc(sizeof(char) * (ft_strlen(src) + (num * 2) + 1));
	if (!dst)
		error_exit("malloc error", info);
	new_sep = ft_strjoin2(" ", sep, " ");
	if (!new_sep)
		error_exit("malloc error", info);
	insert_new_sep(dst, src, sep, new_sep);
	free(src);
	free(new_sep);
	return (dst);
}

void	make_token(t_info *info)
{
	info->line = insert_space(info->line, "|", info);
	info->line = insert_space(info->line, "<<", info);
	info->line = insert_space(info->line, ">>", info);
	info->line = insert_space(info->line, ">", info);
	info->line = insert_space(info->line, "<", info);
	info->token = ft_split2(info->line, "\t\v\f\r ");
	if (!info->token)
		error_exit("split token error", info);
	replace_quote(info);
	replace_g_ret(info);
}
