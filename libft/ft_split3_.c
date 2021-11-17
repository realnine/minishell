#include "libft.h"

char	**ft_split3(char *scr, char *sep)
{
	char	*start;
	char	**ret;
	char	*ptr;
	int		len;

	if (!scr || !sep)
		return (NULL);
	ptr = ft_strdup(scr);
	start = ptr;
	while (*ptr)
	{
		len =  ft_strlen(sep);
		if (ft_strncmp(ptr, sep, len) == 0)
		{
			while (len--)
				*ptr++ = '@';
			ptr--;
		}
		ptr++;
	}
	ret = ft_split(start, '@');
	free(start);
	return (ret);
}
