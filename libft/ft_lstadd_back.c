/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:33:19 by spipitku          #+#    #+#             */
/*   Updated: 2023/09/04 13:36:30 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
}

// #include <stdio.h>

// int main()
// {
//   t_list  *lst;
//   t_list  *new;

//   lst = NULL;
//   new = malloc(sizeof(t_list));
//   new -> content = "Prem";
//   new -> next = NULL;
//   ft_lstadd_back(&lst, new);
//   while(lst)
//   {
//     printf("%s\n",lst->content);
//     lst = lst->next;
//   }
// }
