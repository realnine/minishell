/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinglee <jinglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:19:47 by jinglee           #+#    #+#             */
/*   Updated: 2021/02/12 15:29:58 by jinglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>


int			ft_nbrlen(long int nbr); // added
long int	ft_abs(long int nbr); // added
char		**ft_split2(char *str, char *ch); // added
char		*ft_strjoin2(char *s1, char *s2, char *s3); // added
char		**ft_split3(char *scr, char *sep); // added
int			ft_strcmp(char *s1, char *s2); //added

void	*ft_memset(void *dst, int val, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_memchr(void *src, int c, size_t len);
void	*ft_memccpy(void *dst, const void *src, int c, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);
int		ft_memcmp(const void *ptr1, const void *ptr2, size_t len);
void	ft_bzero(void *str, size_t len);
size_t	ft_strlen(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strncmp(const char *str1, const char *str2, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t len);
char	*ft_strnstr(const char *src, const char *word, size_t range);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t n, size_t sizof);
char	*ft_strdup(const char *str);
char	*ft_substr(char const *src, unsigned int satrt, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif
