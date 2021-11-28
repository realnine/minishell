#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2, char *s3)
{
	char	*ret;
	char	*tmp;

	ret = ft_strjoin(s1, s2);
	tmp = ret;
	ret = ft_strjoin(ret, s3);
	free(tmp);
	return (ret);
}
