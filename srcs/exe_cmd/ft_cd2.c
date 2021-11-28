#include "../../minishell.h"

int	dir_home(char *path, char *arg, t_info *info)
{
	char	*env_val;
	size_t	len;

	env_val = find_env_val("HOME", info->envp);
	if (!env_val)
	{
		if (!arg)
			return (error_print("cd", "HOME not set", NULL, 1));
	}
	else
	{
		len = ft_strlen(env_val) + 1;
		ft_strlcpy(path, env_val, len + 1);
	}
	return (RET_TRUE);
}

int	dir_oldpwd(t_cmd *cur, char *path, t_info *info)
{
	char	*env_val;
	size_t	len;

	env_val = find_env_val("OLDPWD", info->envp);
	if (!env_val)
		return (error_print("cd", "OLDPWD not set", NULL, 1));
	len = ft_strlen(env_val);
	ft_putstr_fd(env_val, cur->fd_out);
	ft_putstr_fd("\n", cur->fd_out);
	ft_strlcpy(path, env_val, len + 1);
	return (RET_TRUE);
}

int	dir_env(char *path, char *arg, t_info *info)
{
	char	*env_val;
	char	*t;
	int		trash;

	trash = 0;
	t = cut_env_name(arg + 1, &trash);
	env_val = find_env_val(t, info->envp);
	ft_free(&t);
	if (!env_val)
		dir_home(path, arg, info);
	else
		ft_strlcpy(path, env_val, ft_strlen(env_val) + 1);
	return (RET_TRUE);
}

int	dir_move(char *path, char ***envp)
{
	char	*tmp;
	char	*ck_env;
	char	buf[PATH_MAX];
	int		ret;

	ret = chdir(path);
	if (ret == -1)
		return (error_print("cd", strerror(errno), NULL, 1));
	tmp = find_env_val("PWD", *envp);
	getcwd(buf, PATH_MAX);
	ck_env = find_env_val("OLDPWD", *envp);
	if (!ck_env)
		*envp = add_env(*envp, ft_strjoin("OLDPWD=", tmp));
	else
		ft_strlcpy(find_env_val("OLDPWD", *envp), tmp, ft_strlen(tmp) + 1);
	ft_strlcpy(tmp, buf, ft_strlen(buf) + 1);
	g_ret_number = 0;
	return (RET_TRUE);
}
