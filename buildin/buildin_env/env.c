/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:42:20 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 18:45:53 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	buildin_env(t_map_list *env, char **cmd)
{
	int	size;

	size = 0;
	while (cmd[size])
		size++;
	if (size > 1)
	{
		write(STDERR_FILENO, "env: ", 5);
		write(STDERR_FILENO, cmd[1], ft_strlen(cmd[1]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return (EXIT_FAILURE);
	}
	while (env)
	{
		if (ft_strcmp(env->key, "_PWD"))
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

void	ft_add_maplist(t_map_list **head, char **src)
{
	t_map_list	*new;
	t_map_list	*temp;

	new = malloc(sizeof(t_map_list));
	new->key = ft_strdup(src[0]);
	if (src[1])
		new->value = ft_strdup(src[1]);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_map_list	*get_env_list(char **env)
{
	size_t		i;
	char		**temp;
	t_map_list	*head;

	head = NULL;
	i = 0;
	while (env[i])
	{
		temp = ft_split(env[i], '=');
		ft_add_maplist(&head, temp);
		ft_free_chrarr(temp);
		free(temp);
		i++;
	}
	temp = NULL;
	return (head);
}

t_map_list	*ft_new_mapnode(char *key, char *value)
{
	t_map_list	*new_node;

	new_node = (t_map_list *)malloc(sizeof(t_map_list));
	if (new_node != NULL)
	{
		new_node->key = ft_strdup(key);
		if (value == 0)
			new_node->value = ft_calloc(1, 1);
		else
			new_node->value = ft_strdup(value);
		new_node->next = NULL;
	}
	return (new_node);
}

t_map_list	*copy_map_list(t_map_list *head)
{
	t_map_list	*new_head;
	t_map_list	*current;
	t_map_list	*new_node;
	t_map_list	*tail;

	if (head == NULL)
		return (NULL);
	new_head = NULL;
	tail = NULL;
	current = head;
	new_node = NULL;
	while (current != NULL)
	{
		new_node = ft_new_mapnode(current->key, current->value);
		if (new_head == NULL)
			new_head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		current = current->next;
	}
	return (new_head);
}
