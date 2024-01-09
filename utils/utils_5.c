/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 20:50:02 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 19:25:40 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strcat(char *dst, char *src)
{
	char	*ptr;

	if (src == NULL)
		return ;
	ptr = dst;
	while (*ptr)
		ptr++;
	while (*src != 0)
		*ptr++ = *src++;
	*ptr = 0;
}

char	*ft_strcpy(char *dst, char *src)
{
	char	*ptr;

	ptr = dst;
	while (*src)
		*ptr++ = *src++;
	*ptr = 0;
	return (dst);
}

void	set_temp_head(t_list **head_temp, t_list *head, t_list **temp)
{
	*head_temp = head;
	*temp = head;
}

void	print_header(t_map_list *env)
{
	(void)env;
	printf("\n");
	printf(" \033[34;5m███╗   ███╗██╗███╗   ██╗██╗\033[0m███████╗██╗  ");
	printf("██╗███████╗██╗     ██╗     \n");
	printf(" \033[34;5m████╗ ████║██║████╗  ██║██║\033[0m██╔════╝██║  ");
	printf("██║██╔════╝██║     ██║     \n");
	printf(" \033[34;5m██╔████╔██║██║██╔██╗ ");
	printf("██║██║\033[0m███████╗███████║█████╗  ██║     ██║     \n");
	printf(" \033[34;5m██║╚██╔╝██║██║██║╚██╗██║██║\033[");
	printf("0m╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
	printf(" \033[34;5m██║ ╚═╝ ██║██║██║ ╚████║██║\033[0m███████║██║  ");
	printf("██║███████╗███████╗███████╗\n");
	printf(" \033[34;5m╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝\033[0m╚══════╝╚═╝  ");
	printf("╚═╝╚══════╝╚══════╝╚══════╝\n\n");
	printf("The default interactive shell is now ");
	printf("on path \033[35;6m%s\033[0m.\n", getenv("SHELL"));
	printf("\033[31;5mBad os detected\033[0m, For more details, please visit ");
	printf("\033[0;33mhttps://www.youtube.com/watch");
	printf("?v=Bu8bH2P37kY\033[0m.\n\n");
}
