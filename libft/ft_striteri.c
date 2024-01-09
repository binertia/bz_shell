/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 07:55:53 by spipitku          #+#    #+#             */
/*   Updated: 2023/09/04 13:31:05 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (*(s + i))
	{
		f(i, s + i);
		i++;
	}
}

/*
#include <stdio.h>
int	main()
{
	char	*s = malloc(3);

	s[0] = 'H';
	s[1] = 'e';
	s[2] = '\0';
	ft_striteri(s, test);
	printf("%s\n",s);
}*/

// LoReM iPsUm
// lOeEm IpSuM
