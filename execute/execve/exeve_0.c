/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeve_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:05:45 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 11:27:35 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execve_child(char **cmd_path, char **env_temp)
{
	signal(SIGINT, SIG_HOLD);
	signal(SIGQUIT, SIG_HOLD);
	if (execve(cmd_path[0], cmd_path, env_temp) == -1)
	{
		perror("minishell: exec child");
		if (errno == 13)
			exit(126);
	}
	exit(EXIT_FAILURE);
}

void	execve_wait_for_child(pid_t *pid, int *return_status, char **cmd,
		char **env)
{
	int	status;

	(void)cmd;
	(void)env;
	waitpid(*pid, &status, 0);
	if (WIFEXITED(status))
		*return_status = get_status(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			printf("^C\n");
			*return_status = 130;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			printf("^\\Quit: 3\n");
			*return_status = 131;
		}
	}
}

int	execve_in_child(int *return_status, char **cmd_path, char **env_temp)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("fork\n");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
		execve_child(cmd_path, env_temp);
	else
	{
		execve_wait_for_child(&pid, return_status, cmd_path, env_temp);
		return (*return_status);
	}
	exit(EXIT_FAILURE);
}

int	check_absolute_command(char **cmd_path, int *status)
{
	struct stat	filestat;

	if (access(cmd_path[0], F_OK) == -1)
	{
		write(2, cmd_path[0], ft_strlen(cmd_path[0]));
		write(2, ": No such file or directory\n", 29);
		*status = 127;
		return (127);
	}
	if (stat(cmd_path[0], &filestat) == 0)
	{
		if (S_ISDIR(filestat.st_mode))
		{
			write(2, cmd_path[0], ft_strlen(cmd_path[0]));
			write(2, ": is a directory\n", 18);
			*status = 126;
			return (126);
		}
	}
	return (0);
}

int	command_not_found_err(char **all_path, char **cmd_path)
{
	ft_free_chrarr(all_path);
	free(all_path);
	all_path = NULL;
	write(2, "minishell: ", 11);
	write(2, cmd_path[0], ft_strlen(cmd_path[0]));
	write(2, ": command not found\n", 20);
	return (127);
}
