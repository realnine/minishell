#include "../minishell.h"

void	two_dimen_str_free(char	**buf)
{
	int	i;

	if (!buf)
		return ;
	i = 0;
	while (buf[i])
	{
		free(buf[i++]);
	}
	free(buf);
}

void	ft_free(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}
