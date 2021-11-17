CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g #-g3 -fsanitize=address

NAME		= minishell
LIBFT		= ./libft/libft.a
RL_FLAG		= -L /usr/local/opt/readline/lib -lreadline -I /usr/local/opt/readline/include
#RL_FLAG		= -lft -L ./libft -lreadline -I /usr/local/opt/readline/include
#RL_FLAG		= -L /Users/jinglee/.brew/opt/readline/lib -lreadline \
				-I /Users/jinglee/.brew/opt/readline/include

SRCS1		= child.c cmd_lst_set.c cmd_lst.c dealloc.c exit.c main.c pipe.c quote.c \
				redirect.c signal.c syntax.c token.c utils_print.c utils.c
SRCS2		= ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c ft_execve.c

SRCS1_PATH	= $(addprefix srcs/, ${SRCS1})
SRCS2_PATH	= $(addprefix srcs/exe_cmd/, ${SRCS2})

all		: ${NAME}

${LIBFT}	:
	${MAKE} -C ./libft/

${NAME}		: ${LIBFT}
	${CC} ${CFLAGS} ${RL_FLAG} ${SRCS1_PATH} ${SRCS2_PATH} ${LIBFT} -o ${NAME}

clean	:
	${MAKE} -C ./libft/ clean

fclean	: clean
	rm -rf ${LIBFT} ${NAME} ${NAME}.dSYM

re		:
	rm -rf ${NAME}
	rm -rf ${LIBFT}
	${MAKE} all

.PHONY : all clean fclean re
