/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:47:41 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/03 19:14:21 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ctype.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <stdint.h>

typedef struct s_list
{
	char			*s;
	struct s_list	*next;
}	t_list;

int		ft_atoi(const char *str);

int		ft_isascii(int c);

int		ft_isalpha(int c);

int		ft_isalnum(int c);

int		ft_isdigit(int c);

int		ft_isprint(int c);

char	*ft_itoa(int n);

size_t	ft_strlen(const char *s);

void	*ft_memset(void *ptr, int x, size_t n);

void	ft_bzero(void *s, size_t n);

void	*ft_memcpy(void *dest, const void *src, size_t n);

void	*ft_memmove(void *to, const void *from, size_t numBytes);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

size_t	ft_strlcat(char *dest, const char *src, size_t size);

char	*ft_strrchr(const char *s, int c);

char	*ft_strchr(const char *s, int c);

int		ft_strncmp(const char *str1, const char *str2, size_t n);

void	*ft_memchr(const void *ptr, int value, size_t n);

int		ft_memcmp(const void *str1, const void *str2, size_t n);

void	ft_putchar_fd(char c, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_putnbr_fd(int n, int fd);

void	ft_putstr_fd(char *s, int fd);

char	**ft_split(char const *s, char c);

char	*ft_strchr(const char *s, int c);

char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlen(const char *s);

char	*ft_strnstr(const char *big, const char *little, size_t len);

int		ft_strncmp(const char *str1, const char *str2, size_t n);

char	*ft_strrchr(const char *s, int c);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_substr(char const *s, unsigned int start, size_t len);

void	*ft_calloc(size_t nmemb, size_t size);

char	*ft_strdup(const char *s);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

int		ft_tolower(int c);

int		ft_toupper(int c);

char	*ft_itoa(int n);

int		count_alpha_of_num_in_n(int n);

void	number_put_in_to_ptr(char **ptr_main, int count, int sum);

t_list	*ft_lstnew(void *content);

void	ft_lstclear(t_list **lst, void (*del)(void*));

t_list	*ft_lstlast(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstdelone(t_list *lst, void (*del)(void*));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstnew(void *content);

int		ft_lstsize(t_list *lst);

void	ft_lstadd_front(t_list **lst, t_list *new);

#endif
