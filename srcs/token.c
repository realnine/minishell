# include "../minishell.h"

int	get_sep_num(char *src, char *sep)
{
	int	num;
	int sep_len;

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
	int sep_len;

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
		error_exit("malloc error\n", info);
	new_sep = ft_strjoin2(" ", sep, " ");
	if (!new_sep)
		error_exit("malloc error\n", info);
	insert_new_sep(dst, src, sep, new_sep);
	free(src);
	free(new_sep);
	return (dst);
}

void	replace_quote(t_info *info)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (info->token[i])
	{
		if (info->token[i][0] == '\"' || info->token[i][0] == '\'')
		{
			tmp = info->token[i];
			info->token[i] = ft_strdup(info->quote_book[j++]);
			if (!info->token[i])
				error_exit("malloc error\n", info);
			free(tmp);
		}
		i++;
	}
}

void	make_token(t_info *info)
{
	// 해당 명령어 사이에 공백 추가 (공백기준으로 분리하기 위함)
	info->line = insert_space(info->line, "|", info); 
	info->line = insert_space(info->line, "<<", info);
	info->line = insert_space(info->line, ">>", info);
	info->line = insert_space(info->line, ">", info);
	info->line = insert_space(info->line, "<", info);

	// 공백을 기준으로 2차원 토큰 배열을 만든다
	info->token = ft_split2(info->line, "\t\v\f\r ");
	if (!info->token)
		error_exit("split token error\n", info);

	// quote 인자가 들어가야할 토큰에 다시 quote buf를 넣어준다 
	// ex) ["000000"] => [hel lo]
	replace_quote(info);

}
