#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

// color
# define SKY	"\x1b[1;34m"
# define RESET	"\x1b[0m"

# define RET_TRUE	1
# define RET_FALSE	0

// pipe fd[]
#define READ    0
#define WRITE   1

# define CMD		"cd echo env exit export pwd unset cat grep ls mkdir rm"
# define REDI		">> > << <"

typedef struct s_cmd
{
	int				token1; // 해당 cmd 의 info->token의 시작 인덱스
	int				token2; // 해당 cmd 의 info->token의 마지막 인덱스

	char			*cmd;
	char			opt;
	char			*arg;
	char			**arg_token;

	char			*redi_in;
	char			*redi_in_arg;
	char			*input_file;

	char			*redi_out;
	char			*redi_out_arg;

	int				fd_in;
	int				fd_out;

	int				*pipe_fd;
	pid_t			pid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_info
{
	int		code; //추추 (error_print)에서 g_ret_number 처리하기 위해 좀 더 나은 방법 없나???고민해보기
	char	**envp;
	char	*line;
	char	**token;
	char	**quote_book;
	//char	*quote_buf;
	int		num_quote;

	char	**cmd_book;
	char	**redi_book;
	int		**pipe_book;
	t_cmd	*cmd_head;
}	t_info;

int	g_ret_number;

// signal
void	set_signal(int mode);

// parse_utils



//syntax_check
int	syntax_check(t_info *info);

// exit
void	error_exit(char *msg, t_info *info);
void	normal_exit(char *msg, t_info *info);
void	child_exit(t_info *info, t_cmd *cur, int ret);


char	*insert_space(char *src, char *sep, t_info *info);
void	make_token(t_info *info);
int		parse_quote(t_info *info);
void	make_child(t_info *info);

int		make_cmd_lst(t_info *info, char **token);
void	set_cmd_lst(t_info *info);

//deallocate
void	reset_free(t_info *info);
void	exit_free(t_info *info);
void	ft_free(char **ptr);

// utils
char	*strtrim_autofree(char *src, char *str, t_info *info);
t_cmd	*creat_cmd_struct(t_info *info);
int		is_cmd(t_info *info, char *token);
int		is_redi(t_info *info, char *token);
int		is_arg(t_info *info, char *token);
int		**ft_malloc_int2(int len, t_info *info);
int		*ft_malloc_int(int len, t_info *info);

//utils_print
void	print_child(t_info *info);
void	print_cmd_lst(t_info *info); 
void	print_token(char **token);
void	print_quote(t_info *info);
void	print_pipe_book(t_info *info);
int		error_print(char *s1, char *s2, char *s3, t_info *info);
int		err_print(char *msg);
// redirection & pipe
int		set_redi_io(t_info *info);
void	make_all_pipe(t_info *info);



// ===============shell_ft=======================
// cd.c
int		is_designate(char *arg);
char	*find_env_val(char *name, char **envp);
int		dir_home(char *path, char *arg, t_info *info);
int		dir_oldpwd(t_cmd *cur, char *path, t_info *info);
int		dir_env(char *path, char *arg, t_info *info);
int		dir_designate(char *path, t_cmd *cur, t_info *info);
void	dir_start_home(char *path, char *arg, char **envp);
char	**add_env(char **envp, char *str);
int		dir_move(char *path, char ***envp, t_info *info);
int		ft_cd(t_info *info, t_cmd *cur);

//echo.c
char	*ft_strjoin_free(char *s1, char *s2, int flag);
char	*cut_env_name(char *arg, int *i, t_info *info);
void	ft_echo(t_info *info, t_cmd *cur);
//env.c
int		env_denied(t_info *info, char *arg);
int		ft_env(t_info *info, t_cmd *cur);

//exit.c
void	ft_exit(t_info *info, t_cmd *cur);

//export.c
int		ft_strslen(char **strs);
int		is_export_normal(char *arg);
char	**copy_envp(char **envp, int add);
char	**sort_export(char **envp);
void	set_export_print(t_cmd *cur, char **envp, t_info *info);
char	*ft_charjoin(char *str, char c);
char	*export_etc(char *arg, char **envp, char *str, t_info *info);
int		is_exist_env(char *name, char **envp);
int		add_export(char *arg, char ***envp, t_info *info);
int		ft_export(t_info *info, t_cmd *cur);

//pwd.c
void	ft_pwd(t_cmd *cur);
//unset.c
int		remove_env(char ***envp, int pos);
int		ft_unset(t_info *info, t_cmd *cur);

void	ft_execve(t_info *info, t_cmd *cur);

#endif