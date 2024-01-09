/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:00:20 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 11:44:08 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_node_cmp_remove(t_map_list **env, char *str)
{
	t_map_list	*temp;

	if (*env == NULL)
		return ;
	if (ft_strcmp((*env)->key, str) == 0)
	{
		temp = *env;
		*env = (*env)->next;
		free(temp->key);
		temp->key = NULL;
		free(temp->value);
		temp->value = NULL;
		free(temp);
		temp = NULL;
		return ;
	}
	ft_node_cmp_remove(&(*env)->next, str);
}

int	check_valid_unset(char *s)
{
	size_t	i;

	i = 0;
	if (ft_strchr("~!@#$%^&*()+1234567890-={}[]\\|:;?/.,<>`", s[i]))
		return (0);
	i++;
	while (s[i] && ft_strchr("!@#$%^&*()+--=\'\"\\|:;/?<>~`~`[]{}",
			s[i]) == NULL)
		i++;
	if (s[i])
		return (0);
	return (1);
}

int	buildin_unset(t_map_list **env, char **cmd)
{
	size_t	i;
	int		status;

	i = 1;
	status = 0;
	while (cmd[i])
	{
		if (ft_strstr(cmd[i], "_PWD"))
			return (status);
		if (cmd[i][0] && check_valid_unset(cmd[i]))
			ft_node_cmp_remove(env, cmd[i]);
		else
		{
			status = 1;
			write(2, "minishell: unset: `", 19);
			write(2, cmd[i], ft_strlen(cmd[i]));
			write(2, "`: not a valid identifier\n", 26);
		}
		i++;
	}
	return (status);
}
