#include "../minishell.h"

int	**ft_malloc_int2(int len, t_info *info)
{
	int	**ret;

	ret = (int **)malloc(sizeof(int *) * len);
	if (!ret)
		error_exit("malloc err\n", info);
	return (ret);
}

int	*ft_malloc_int(int len, t_info *info)
{
	int	*ret;

	ret = (int *)malloc(sizeof(int) * len);
	if (!ret)
		error_exit("malloc err\n", info);
	return (ret);
}

char	*strtrim_autofree(char *src, char *str, t_info *info)
{
	char	*dst;

	dst = ft_strtrim(src, str);
	free(src);
	if (!dst)
		error_exit("ft_strtrim error\n", info);
	return (dst);
}

t_cmd	*creat_cmd_struct(t_info *info)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		error_exit("malloc error\n", info);
	cmd->token1 = 0;
	cmd->token2 = 0;
	cmd->cmd = NULL;
	cmd->opt = '\0';
	cmd->arg = NULL;
	cmd->arg_token = NULL;
	cmd->redi_in = NULL;
	cmd->redi_in_arg = NULL;
	cmd->input_file = NULL;
	cmd->redi_out = NULL;
	cmd->redi_out_arg = NULL;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->pipe_fd = NULL;
	cmd->pid = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}
