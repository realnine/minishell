#include "../../minishell.h"

int	not_interpre(char **str)
{
	int	len;

	len = ft_strlen(*str);
	if ((*str)[0] == '\'' && (*str)[len - 1] == '\'')
	{
		remove_q(*str, '\'');
		return (RET_TRUE);
	}
	return (RET_FALSE);
}

char	*fill_interpre(t_info *info, t_cmd *cur, int	i, int *j)
{
	char	*name;
	char	*val;
	char	*ret;

	(*j)++;
	ret = NULL;
	name = cut_env_name(cur->arg_token[i] + (*j), j);
	val = find_env_val(name, info->envp);
	ret = ft_strjoin_free(ret, val, 1);
	ft_free(&name);
	return (ret);
}

char	*fill_str(t_info *info, t_cmd *cur, int i)
{
	char	*tmp;
	char	*ret;
	int		j;

	ret = NULL;
	tmp = NULL;
	if (not_interpre(&cur->arg_token[i]))
		ret = ft_strjoin_free(ret, cur->arg_token[i], 1);
	else
	{
		j = -1;
		while (cur->arg_token[i][++j])
		{
			if (cur->arg_token[i][j] == '$' && cur->arg_token[i][j + 1] \
				&& cur->arg_token[i][j + 1] != '\0')
			{
				tmp = fill_interpre(info, cur, i, &j);
				ret = ft_strjoin_free(ret, tmp, 3);
			}
			else if (cur->arg_token[i][j])
				ret = ft_charjoin(ret, cur->arg_token[i][j]);
			remove_q(ret, '\"');
		}
	}
	return (ret);
}

char	*set_echo(t_info *info, t_cmd *cur)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = -1;
	ret = NULL;
	while (cur->arg_token[++i])
	{
		tmp = fill_str(info, cur, i);
		tmp = ft_charjoin(tmp, ' ');
		ret = ft_strjoin_free(ret, tmp, 3);
	}
	return (ret);
}

int	ft_echo(t_info *info, t_cmd *cur)
{
	char	*str;

	str = NULL;
	if (!cur->arg_token)
		str = ft_strdup("");
	else
		str = set_echo(info, cur);
	ft_putstr_fd(str, cur->fd_out);
	if (cur->opt != 'n')
		ft_putchar_fd('\n', cur->fd_out);
	ft_free(&str);
	(void)info;
	g_ret_number = 0;
	return (RET_TRUE);
}
