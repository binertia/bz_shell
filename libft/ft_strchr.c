/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:38:40 by spipitku          #+#    #+#             */
/*   Updated: 2023/09/04 13:30:09 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	const char		*ptr;

	ptr = s;
	i = 0;
	c = (unsigned char)c;
	while (*(s + i))
	{
		if (*(s + i) == c)
			return ((char *)(ptr + i));
		i++;
	}
	if (i == ft_strlen(s) && c == 0)
		return ((char *)(ptr + i));
	return (0);
}

/*
#include <string.h>
#include <stdio.h>
int	main()
{
	printf("%s\n",ft_strchr(NULL,NULL));
}*/
