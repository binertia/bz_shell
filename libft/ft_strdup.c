/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:33:05 by spipitku          #+#    #+#             */
/*   Updated: 2023/09/04 13:30:33 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char		*ptr;
	size_t		i;

	i = 0;
	ptr = malloc(ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	while (*(s + i))
	{
		ptr[i] = *(s + i);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
