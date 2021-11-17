/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinglee <jinglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:30:01 by jinglee           #+#    #+#             */
/*   Updated: 2021/02/08 16:05:25 by jinglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	srcsize;

	if (!dst || !src)
		return (0);
	srcsize = ft_strlen(src);
	if (n == 0)
		return (srcsize);
	if (srcsize < n)
		ft_memcpy(dst, src, srcsize + 1);
	if (srcsize >= n)
	{
		ft_memcpy(dst, src, n - 1);
		dst[n - 1] = '\0';
	}
	return (srcsize);
}
