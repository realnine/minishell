#include "libft.h"

char	**ft_split2(char *str, char *ch)
{
	char	*start;
	char	**ret;
	char	*ptr;

	if (!str || !ch)
		return (NULL);
	ptr = ft_strdup(str);
	start = ptr;
	while (*ptr)
	{
		if (ft_strchr(ch, *ptr))
			*ptr = ch[0];
		ptr++;
	}
	ret = ft_split(start, ch[0]);
	free(start);
	return (ret);
}
