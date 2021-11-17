/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinglee <jinglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:45:31 by jinglee           #+#    #+#             */
/*   Updated: 2021/02/10 14:51:01 by jinglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	res;

	sign = 1;
	res = 0;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign = -1;
	}
	while (ft_isdigit(*str))
		res = res * 10 + (*str++ - '0');
	if (res > INT_MAX && sign == 1)
		return (-1);
	if (res > 2147483648 && sign == -1)
		return (0);
	return (res * sign);
}
