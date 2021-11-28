#include "../minishell.h"

char	*ft_charjoin(char *str, char c)
{
	char	*new;
	int		len;
	int		i;

	len = ft_strlen(str);
	if (c == '\n')
		return (str);
	else
	{
		new = (char *)malloc(sizeof(char) * (len + 2));
		i = -1;
		if (str == NULL)
			new[0] = c;
		else
		{
			while (str[++i])
				new[i] = str[i];
			new[i] = c;
			ft_free(&str);
		}
		new[len + 1] = '\0';
	}
	return (new);
}

int	ft_strslen(char **strs)
{
	int	len;

	len = 0;
	if (!strs)
		return (0);
	while (strs[len])
		len++;
	return (len);
}
