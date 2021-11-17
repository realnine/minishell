/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinglee <jinglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:24:01 by jinglee           #+#    #+#             */
/*   Updated: 2021/02/12 15:44:04 by jinglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive(int n, int fd, char *decimal)
{
	if (n / 10 != 0)
		ft_recursive(n / 10, fd, decimal);
	if (n >= 0)
		write(fd, &decimal[n % 10], 1);
	else if (n < 0)
		write(fd, &decimal[-(n % 10)], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	*decimal;

	decimal = "0123456789";
	if (n < 0)
		write(fd, "-", 1);
	ft_recursive(n, fd, decimal);
}
