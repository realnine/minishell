#include "../minishell.h"

void	init_info(t_info *info)
{
	info->line = NULL;
	info->cmd_head = NULL;
	info->cmd_book = ft_split(CMD, ' ');
	if (!info->cmd_book)
		error_exit("malloc\n", info);
	info->redi_book = ft_split(REDI, ' ');
	if (!info->redi_book)
		error_exit("malloc\n", info);
	info->token = NULL;
	info->num_quote = 0;
	info->quote_book = NULL;
	info->pipe_book = NULL;
	info->idx_q = 0;
	tcgetattr(STDIN_FILENO, &(info->term));
	tcgetattr(STDIN_FILENO, &(info->org_term));
	info->term.c_lflag &= ~ECHOCTL;
}

void	prompt(t_info *info)
{
	char	path[PATH_MAX];
	int		len;
	char	*str;

	getcwd(path, PATH_MAX);
	len = ft_strlen(path);
	path[len] = '$';
	path[len + 1] = ' ';
	path[len + 2] = '\0';
	str = ft_strjoin2(SKY, path, RESET);
	if (!str)
		error_exit("strjoin error\n", info);
	tcsetattr(STDIN_FILENO, TCSANOW, &(info->term));
	info->line = readline(str);
	free(str);
	tcsetattr(STDIN_FILENO, TCSANOW, &info->org_term);
}

char	**set_env(t_info *info, char **env)
{
	char	**new;
	int		i;

	i = 0;
	while (env[++i] != NULL)
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new)
		error_exit("malloc error", info);
	i = -1;
	while (env[++i])
	{
		new[i] = (char *)malloc(sizeof(char) * PATH_MAX + 1);
		ft_strlcpy(new[i], env[i], ft_strlen(env[i]) + 1);
		if (!new[i])
			error_exit("malloc error", info);
	}
	new[i] = NULL;
	return (new);
}

void	main_routine(t_info *info)
{
	info->line = strtrim_autofree(info->line, "\t\v\f\r ", info);
	if (info->line[0] == '\0')
		return ;
	if (parse_quote(info) == RET_FALSE)
		return ;
	make_token(info);
	if (syntax_check(info) == RET_FALSE)
		return ;
	if (make_cmd_lst(info, info->token) == RET_FALSE)
		return ;
	make_all_pipe(info);
	make_child(info);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	(void)argc;
	(void)argv;
	info.envp = set_env(&info, envp);
	init_info(&info);
	g_ret_number = 1;
	while (1)
	{
		set_signal(1);
		prompt(&info);
		if (!info.line)
			error_exit("exit", &info);
		if (ft_strlen(info.line) > 0)
			add_history(info.line);
		if (info.line)
			main_routine(&info);
		reset_free(&info);
	}
	return (0);
}
