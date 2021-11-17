/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinglee <jinglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 21:24:48 by jinglee           #+#    #+#             */
/*   Updated: 2021/02/12 15:42:04 by jinglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_scale(int n)
{
	size_t	c;

	c = 1;
	if (n < 0)
		c++;
	while (n / 10 != 0)
	{
		c++;
		n /= 10;
	}
	return (c);
}

static char	*ft_rec(int n, char *str, char *decimal)
{
	if (n / 10 != 0)
		str = ft_rec(n / 10, str, decimal);
	if (n < 0)
		*str = decimal[-(n % 10)];
	else
		*str = decimal[n % 10];
	return (++str);
}

char	*ft_itoa(int n)
{
	char	*str;
	char	*decimal;
	char	*str0;

	decimal = "0123456789";
	str = malloc(sizeof(char) * (ft_scale(n) + 1));
	if (!str)
		return (NULL);
	str0 = str;
	if (n < 0)
		*str++ = '-';
	str = ft_rec(n, str, decimal);
	*str = '\0';
	return (str0);
}
