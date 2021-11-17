/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinglee <jinglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:36:18 by jinglee           #+#    #+#             */
/*   Updated: 2021/02/08 16:08:39 by jinglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*p;

	p = NULL;
	while (1)
	{
		if (*str == (char)c)
			p = (char *)str;
		if (*str == '\0')
			return (p);
		str++;
	}
}
