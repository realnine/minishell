/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinglee <jinglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:33:21 by jinglee           #+#    #+#             */
/*   Updated: 2021/02/11 22:55:53 by jinglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_mulfree(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

static int	ft_parent_siz(char const *s, char c)
{
	int	cnt;

	cnt = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			cnt++;
			while (*s != c && *s)
				s++;
		}
	}
	return (cnt);
}

static int	ft_child_siz(char const *s, char c)
{
	int	cnt;

	cnt = 0;
	if (!s)
		return (0);
	while (*s != c && *s)
	{
		cnt++;
		s++;
	}
	return (cnt);
}

char	**ft_split(char const *s, char c)
{
	char	**mul_ptr;
	int		parent_siz;
	int		child_siz;
	int		i;

	parent_siz = ft_parent_siz(s, c);
	mul_ptr = ft_calloc(parent_siz + 1, sizeof(char *));
	if (!s || !mul_ptr)
		return (NULL);
	i = 0;
	while (i < parent_siz)
	{
		while (*s == c && *s)
			s++;
		child_siz = ft_child_siz(s, c);
		mul_ptr[i] = malloc(child_siz + 1);
		if (!mul_ptr[i])
		{
			ft_mulfree(mul_ptr);
			return (NULL);
		}
		ft_strlcpy(mul_ptr[i++], s, child_siz + 1);
		s += child_siz;
	}
	return (mul_ptr);
}
