/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:03:26 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/06 23:44:50 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strnum_exit(char *s)
{
	int	count;

	count = 0;
	if (s == NULL || *s == 0)
		return (0);
	if (ft_strchr("-+", *s))
		s++;
	while (*s)
	{
		count++;
		if ((*s >= '0' && *s <= '9'))
			s++;
		else
			break ;
	}
	if (*s == 0 && count)
		return (1);
	return (0);
}

long long	ft_atoll(char *s)
{
	long long	state;
	long long	res;

	state = 0;
	res = 0;
	if (*s == '-')
		state = 1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
		res = (res * 10) + (*s++ - '0');
	if (state)
		return (res * -1);
	if (res > 9223372036854775807 || res < -9223372036854775807)
		return (255);
	return (res);
}

int	over_llong_minus(char *s)
{
	char	*llong;

	llong = "9223372036854775808";
	if (ft_strlen(s) < 19)
		return (VALID_LLONG);
	else if (ft_strlen(s) >= 20 || ft_strcmp(s, llong) > 0)
		return (-1);
	else if (ft_strcmp(s, llong) == 0)
		return (0);
	return (VALID_LLONG);
}

int	over_llong_plus(char *s)
{
	char	*llong;

	llong = "9223372036854775807";
	if (ft_strlen(s) >= 20)
		return (-1);
	else if (ft_strlen(s) < 19)
		return (VALID_LLONG);
	if (ft_strcmp(s, llong) >= 0)
		return (-1);
	return (VALID_LLONG);
}

int	handle_over_llong(char *s)
{
	if (*s == '-')
	{
		s++;
		while (*s && *s == '0')
			s++;
		return (over_llong_minus(s));
	}
	else
	{
		while (*s && *s == '0')
			s++;
		return (over_llong_plus(s));
	}
	return (VALID_LLONG);
}
