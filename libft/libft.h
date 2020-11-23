/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bminner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:51:49 by bminner           #+#    #+#             */
/*   Updated: 2019/10/28 15:21:21 by bminner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int val);
int				ft_tolower(int val);
size_t			ft_strlen(const char *src);
char			*ft_strchr(const char *str, int c);
void			*ft_memset(void *src, int c, size_t n);
void			ft_bzero(void *src, size_t n);
void			*ft_memcpy(void *str1, const void *str2, size_t n);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	        ft_strlcpy(char *dest, const char *src, size_t size);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *str, int c, size_t n);
int				ft_memcmp(const void *str1, const void *str2, size_t n);
void			*ft_memmove(void *str1, const void *str2, size_t n);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *hay, const char *needle, size_t len);
void			*ft_calloc(size_t nitems, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
char			**ft_split(char const *s, char c);
int				ft_len(long n);
char			*ft_itoa(int n);
char			*ft_strndup(const char *s, size_t n);
char			*ft_strncpy(char *dest, const char *s, size_t n);
char			*ft_strtrim(char const *s1, char const *set);
void			ft_bzero(void *src, size_t n);

#endif
