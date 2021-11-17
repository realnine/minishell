#include "libft.h"

long int	ft_abs(long int nbr)
{
	if (nbr < 0)
		nbr *= -1;
	return (nbr);
}
