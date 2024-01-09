/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 00:13:36 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 18:28:26 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_str(char **str, t_map_list *env, int status)
{
	t_list	*head;
	t_list	*head_temp;
	size_t	len;
	t_list	*temp;
	char	*res;

	len = 0;
	if (*str == 0 || **str == 0 || is_parse_able(*str) == 0)
		return ;
	head = get_replaced(*str, env, status);
	if (head == NULL)
		return ;
	set_temp_head(&head_temp, head, &temp);
	while (temp)
		replace_str_moving_ptr(&temp, &len);
	res = ft_calloc(len + 1, 1);
	while (head)
	{
		if (head->s && head->s[0])
			ft_strcat(res, head->s);
		head = head->next;
	}
	ft_free_list(head_temp);
	free(*str);
	*str = res;
}

void	setup(t_map_list *env)
{
	char	*temp[6];
	char	*shlvl;
	char	*lvl;

	install_term();
	lvl = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
	shlvl = ft_calloc(ft_strlen(lvl) + 7, 1);
	ft_strcat(shlvl, "SHLVL=");
	ft_strcat(shlvl, lvl);
	free(lvl);
	temp[0] = "export";
	temp[1] = shlvl;
	temp[2] = "CLICOLOR=1";
	temp[3] = "LSCOLORS=ExFxCxDxBxegedabagacad";
	temp[4] = "GREP_OPTIONS=--color=auto";
	temp[5] = NULL;
	buildin_export(env, temp, 0, 0);
	free(shlvl);
}

void	set_add_history(char *input, t_map_list **env, int *g_status,
		t_exec **head)
{
	add_history(input);
	run_line(input, env, g_status, head);
}
