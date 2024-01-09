/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:46:57 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/03 14:47:06 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ----------- group token list ------

t_tok_list	*ft_new_toklist(void)
{
	t_tok_list	*new;

	new = malloc(sizeof(t_tok_list));
	new->token = ARGS_TYPE;
	new->str = NULL;
	new->next = NULL;
	new->child = NULL;
	return (new);
}

int	ft_strnum(char *s)
{
	while ((*s >= '0' && *s <= '9') || *s == '&')
		s++;
	if (*s == 0)
		return (1);
	return (0);
}
