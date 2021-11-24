#include "../../minishell.h"
//g_ret_number
//arg ck
int	is_designate(char *arg)
{
	return (!arg || !ft_strcmp("~", arg) || !ft_strcmp("~/", arg) || !ft_strcmp("-", arg) || !ft_strncmp("$", arg, 1));
}

char	*find_env_val(char *name, char **envp)
{
	int	i;
	const int	len = ft_strlen(name);

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(name, envp[i], len))
			if (envp[i][len] == '=')
				return (ft_strchr(envp[i], '=') + 1);
	}
	return (NULL);
}

int	dir_home(char *path, char *arg, t_info *info)
{
	char	*env_val;
	size_t	len;

	env_val = find_env_val("HOME", info->envp);
	if (!env_val)
	{
		if (!arg)
			return (error_print("cd", "HOME not set", NULL, 1)); //error_print 인자 생각해보기
	}
	else
	{
		len = ft_strlen(env_val) + 1; //? 나중에 확인
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
		return (error_print("cd", "OLDPWD not set", NULL, 1)); //error_print
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
	int	trash;

	t = cut_env_name(arg + 1, &trash);
	env_val = find_env_val(t, info->envp); //수정??
	ft_free(&t);
	if (!env_val)
		dir_home(path, arg, info);
	else
		ft_strlcpy(path, env_val, ft_strlen(env_val) + 1);
	return (RET_TRUE);
}

int	dir_designate(char *path, t_cmd *cur, t_info *info)
{
	if (!cur->arg || !ft_strcmp("~", cur->arg) || !ft_strcmp("~/", cur->arg))
	{
		if (!dir_home(path, cur->arg, info)) //ok
			return (RET_FALSE);
	}
	else if (!ft_strcmp("-", cur->arg))
	{
		if (!dir_oldpwd(cur, path, info)) //ok
			return (RET_FALSE);
	}
	else if (!ft_strncmp("$", cur->arg, 1)) //ok
	{
		if (!dir_env(path, cur->arg, info))
			return (RET_FALSE);
	}
	return (RET_TRUE);
}

void	dir_start_home(char *path, char *arg, char **envp)
{
	int	i;
	int	j;
	char	*env_val;

	env_val = find_env_val("HOME", envp);
	i = -1;
	while (env_val[++i])
		path[i] = env_val[i];
	j = 1;
	while (arg[j])
		path[i++] = arg[j++];
}

char	**add_env(char **envp, char *str)
{
	char	**new;
	int	i;

	i = 0;
	while (envp[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = -1;
	while(envp[++i])
		new[i] = envp[i];
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	free(str);
	free(envp);
	return (new);
}

int	dir_move(char *path, char ***envp)
{
	int	ret;
	char	*tmp;
	char	*ck_env;
	char	buf[PATH_MAX];

	ret = chdir(path);
	if (ret == -1)
		return(error_print("cd", strerror(errno), NULL, 1));
	tmp = find_env_val("PWD", *envp);
	getcwd(buf, PATH_MAX);
	ck_env = find_env_val("OLDPWD", *envp);
	if (!ck_env)
		*envp = add_env(*envp, ft_strjoin("OLDPWD=", tmp));
	else
		ft_strlcpy(find_env_val("OLDPWD", *envp), tmp, ft_strlen(tmp) + 1);
	ft_strlcpy(tmp, buf, ft_strlen(buf) + 1);
	g_ret_number = 0; //추추
	return (RET_TRUE);
}

int	ft_cd(t_info *info, t_cmd *cur)
{
	char	path[PATH_MAX + 1];
	int	i;
	const int	len = ft_strlen(cur->arg);

	printf("arg = [%s]\n", cur->arg);
	i = -1;
	ft_memset(path, 0, sizeof(path));
	if (is_designate(cur->arg)) //ok
	{
		if (!dir_designate(path, cur, info)) //ok
			return (RET_FALSE);
	}
	else if (cur->arg[0] == '~' && cur->arg[1] == '/' && len > 2)
		dir_start_home(path, cur->arg, info->envp); //ok
	else
		while (cur->arg[++i])
			path[i] = cur->arg[i];
	dir_move(path, &info->envp);
	return (RET_TRUE);
}
