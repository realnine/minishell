# include "../minishell.h"

void	init_info(t_info *info)
{
	info->code = 0; //추추
	info->line = NULL;
	info->cmd_head = NULL;
	info->cmd_book = ft_split(CMD, ' ');   // echo cd ls ...  리스트 
	if (!info->cmd_book)
		error_exit("malloc\n", info);
	info->redi_book = ft_split(REDI, ' ');  // << < > >> |  리스트
	if (!info->redi_book)
		error_exit("malloc\n", info);
	info->token = NULL;
	info->num_quote = 0;
	info->quote_book = NULL;
	info->idx_q = 0;
}

void	prompt(t_info *info)
{
	char	path[200];
	int		len;
	char	*str;

	getcwd(path, 200);
	len = ft_strlen(path);
	path[len] = '$';
	path[len + 1] = ' ';
	path[len + 2] = '\0';
	str = ft_strjoin2(SKY, path, RESET);
	if (!str)
		error_exit("strjoin error\n", info);
	info->line = readline(str);
	free(str);
}

char	**set_env(char **env)
{
	char	**new;
	int	i;

	i = 0;
	while (env[++i] != NULL)
		i++;
	if (!(new = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = -1;
	while (env[++i])
		new[i] = ft_strdup(env[i]);
	new[i] = NULL;
	return (new);
}

void	main_routine(t_info *info)
{
	// ft_strtrim 기능인데 자동 free기능 추가해서 만듦
	info->line = strtrim_autofree(info->line, "\t\v\f\r ", info);
	//printf("\nline : [%s]\n", info->line);

	if (info->line[0] == '\0')
		return ;
		
	// quote " ' 처리
	if (parse_quote(info) == RET_FALSE)
		return ;
		//print_quote(info);


	make_token(info);
		//print_token(info->token);
		
	if (syntax_check(info) == RET_FALSE)
		return ;

	// 파이프 기준으로 cmd리스트를 새로 만들고 값을 세팅한다
	if (make_cmd_lst(info, info->token) ==  RET_FALSE)
		return ;
		//print_cmd_lst(info);

	make_all_pipe(info);// 모든 파이프를 생성, (info->pipe_book)
		//print_pipe_book(info);
	
	if (set_redi_io(info) == RET_FALSE)
		return ;

	make_child(info);
		//print_child(info);
}

int main(int argc, char **argv, char **envp)
{
	t_info	info;

	(void)argc;
	(void)argv;
	info.envp = set_env(envp);
	init_info(&info);
	while (1)
	{
		set_signal(1);
		prompt(&info);
		if (!info.line)
		{
			printf("pressed ctrl + d\n");
			error_exit("exit", &info); // ctrl + d 를 누르면 여기로
		}
		if (ft_strlen(info.line) > 0)
			add_history(info.line);
		if (info.line)
			main_routine(&info);
		reset_free(&info);
	}
	return (0);
}
