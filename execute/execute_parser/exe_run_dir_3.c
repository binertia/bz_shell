/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_run_dir_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:23:41 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/04 11:07:14 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_redir(t_exec *data, t_map_list *env, int status, int f_redir)
{
	int			b_redir;
	char		*file_name;
	t_redirect	*redir;
	int			check;

	if (setup_run_redir(&file_name, &redir, data) == 1)
		return (0);
	while (redir)
	{
		setup_redir(redir, &f_redir, &b_redir, &check);
		if (redir->back_fd)
		{
			replace_str(&(redir->back_fd), env, status);
			unquote_and_add_target_fd_ref(redir, &b_redir, &file_name, &check);
			if (check == 0 && bad_filename(redir, &file_name) == 1)
				return (EXIT_FAILURE);
		}
		else if (data->next && data->next->run_condition == ARGS_TYPE)
			getfd_ref_from_next_args(&data, env, &status, &file_name);
		else
			return (EXIT_FAILURE);
		if (start_run_redir(&redir, &file_name, f_redir, b_redir) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	setup_getcmd(size_t *count, t_list **temp, int *i, t_list *cmd)
{
	*i = 0;
	*count = 0;
	while (cmd)
	{
		*count += 1;
		cmd = cmd->next;
	}
	*temp = cmd;
}

void	*get_cmd_arr_free_return(char **res)
{
	if (res)
	{
		ft_free_chrarr(res);
		free(res);
	}
	return (NULL);
}

char	**get_cmd_arr(t_list *cmd, t_map_list *env, int status)
{
	char	**res;
	size_t	count;
	t_list	*temp;
	int		i;

	setup_getcmd(&count, &temp, &i, cmd);
	res = (char **)ft_calloc(count + 1, sizeof(char *));
	while (cmd)
	{
		replace_str(&cmd->s, env, status);
		if (cmd->s && cmd->s[0])
		{
			res[i] = ft_strdup(cmd->s);
			unquote_realloc_str(&res[i]);
			i++;
		}
		cmd = cmd->next;
	}
	if (res[0] == 0 || res[0][0] == 0)
		return (get_cmd_arr_free_return(res));
	return (res);
}

size_t	ft_map_len(t_map_list *env)
{
	size_t	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}
