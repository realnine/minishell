# include "../../minishell.h"

char	*cut_env_name(char *arg, int *i, t_info *info)
{
	int	len;
	char	*res;

	len = 0;
	if (arg[len] == '?') //추추(수정필요)
		len++;
	else
		while (arg[len] && (ft_isalpha(arg[len]) || arg[len] == '_'))
			len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		error_exit("malloc error\n", info);
	ft_memcpy(res, arg, len);
	*i += len - 1;
	return (res);
}

void	ft_echo(t_info *info, t_cmd *cur) //echo $? 만들기
{
	char	*env_val;
	char	*res;
	int	i;

	i = -1;
	while (cur->arg[++i])
	{
		if (cur->arg[i] == '$' && cur->arg[i + 1] && cur->arg[i + 1] != '\0')
		{
			i++;
			res = cut_env_name(cur->arg + i, &i, info);
			env_val = find_env_val(res, info->envp);
			ft_putstr_fd(env_val, cur->fd_out);
		}
		else
			ft_putchar_fd(cur->arg[i], cur->fd_out);
	}
	if (cur->opt != 'n')
		ft_putchar_fd('\n', cur->fd_out);
	g_ret_number = 0; //추추
}