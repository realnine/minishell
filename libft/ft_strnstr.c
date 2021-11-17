/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinglee <jinglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:47:54 by jinglee           #+#    #+#             */
/*   Updated: 2021/02/08 16:24:56 by jinglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *word, size_t range)
{
	size_t	word_len;
	int		res;

	word_len = ft_strlen(word);
	if (*word != '\0')
	{
		if (range == 0)
			return (NULL);
		while (1)
		{
			res = ft_strncmp(src, word, word_len);
			if (res == 0)
				break ;
			else if (*++src == '\0' || --range < word_len)
				return (NULL);
		}
	}
	return ((char *)src);
}
