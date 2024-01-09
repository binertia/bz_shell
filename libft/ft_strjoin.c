/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:21:08 by spipitku          #+#    #+#             */
/*   Updated: 2023/09/04 13:31:33 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_s1_s2_to_ptr(char **ptr, char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
		(*ptr)[j++] = s1[i++];
	i = 0;
	while (i < ft_strlen(s2))
		(*ptr)[j++] = s2[i++];
	return (j);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		sum_len;
	char		*ptr;
	size_t		i;

	i = 0;
	if (!s2 || !s1)
		return (NULL);
	if (!*s1 && !*s2)
		return (ft_strdup(""));
	sum_len = ft_strlen(s1) + ft_strlen(s2);
	if (sum_len == 0)
		return ((char *)0);
	ptr = malloc(sum_len + 1);
	if (!ptr)
		return (ptr);
	i = put_s1_s2_to_ptr(&ptr, s1, s2);
	ptr[i] = '\0';
	return (ptr);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char *s1 = "H";
// 	char *res = ft_strjoin(s1,NULL);
// 	if (res == NULL)
// 		printf("Hello\n");
// }
