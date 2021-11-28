#include "../../minishell.h"

int	set_export_print(t_cmd *cur, char **envp)
{
	char	**sorted;
	int		i;

	sorted = set_export(envp);
	i = -1;
	while (sorted[++i])
		export_print(cur, sorted, i);
	i = -1;
	while (sorted[++i])
		ft_free(&sorted[i]);
	free(sorted);
	sorted = NULL;
	return (RET_TRUE);
}

char	**set_export(char **envp)
{
	char	**copy;
	int		i;

	copy = (char **)malloc(sizeof(char *) * (ft_strslen(envp) + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (envp[++i])
		copy[i] = ft_strdup(envp[i]);
	copy[i] = NULL;
	sort_export(&copy, i);
	return (copy);
}

void	sort_export(char ***copy, int i)
{
	int		j;
	char	*tmp;

	while (--i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strcmp((*copy)[j], (*copy)[j + 1]) > 0)
			{
				tmp = (*copy)[j + 1];
				(*copy)[j + 1] = (*copy)[j];
				(*copy)[j] = tmp;
			}
			j++;
		}
	}
}

void	export_print(t_cmd *cur, char **sorted, int i)
{
	char	*str;
	char	*env_val;
	char	*env_name;
	int		trash;

	str = ft_strdup("declare -x ");
	env_name = cut_env_name(sorted[i], &trash);
	str = ft_strjoin_free(str, env_name, 1);
	env_val = find_env_val(env_name, sorted);
	if (env_val)
	{
		str = ft_strjoin_free(str, "=\"", 1);
		str = ft_strjoin_free(str, env_val, 1);
		str = ft_charjoin(str, '\"');
	}
	ft_putstr_fd(str, cur->fd_out);
	ft_putchar_fd('\n', cur->fd_out);
	ft_free(&env_name);
	ft_free(&str);
	env_val = NULL;
}
