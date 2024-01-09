/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:41:44 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/09 09:46:51 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void sigint_hered(int signum, siginfo_t *info, void *context)
{
	int *status;

	(void)signum;
	(void)context;
	status = info->si_value.sival_ptr;
	printf("got sigint; it workkkkk!");
    *status = 1;
}

static void	sig_for_hered(void)
{
    struct sigaction sa;

    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = &sigint_hered;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags |= SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
}


void	heredoc_input_process(t_pipe *pipe_fd, char *eof)
{
	char	*input;

	int		status;
	status = 0;
	sig_for_hered();

	input = NULL;
	close((*pipe_fd).read_fd);
	while (status == 0)
	{
		input = readline("heredoc> ");
		if (status == 1 || input == 0 || ft_strcmp(input, eof) == 0)
		{
			free(input);
			break ;
		}
		write((*pipe_fd).write_fd, input, ft_strlen(input));
		write((*pipe_fd).write_fd, "\n", 1);
		free(input);
	}
	if (status == 1)
	{
		close((*pipe_fd).write_fd);
		exit(EXIT_FAILURE);
	}
	write((*pipe_fd).write_fd, "\n", 1);
	close((*pipe_fd).write_fd);
	exit(EXIT_SUCCESS);
}

int	heredoc_parent_handle_error(t_pipe *pipe_fd, char *eof, pid_t pid,
		int *res_status)
{
	int	status;

	(void)eof;
	close((*pipe_fd).write_fd);
	sig_ignore();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*res_status = 0;
	else if (WIFSIGNALED(status))
	{
		printf("\n");
		*res_status = 1;
		close((*pipe_fd).read_fd);
		*res_status = 1;
		return (1);
	}
	return (0);
}

void	heredoc_set_line(char **result, char **line, int line_count, int *i)
{
	ft_strcat(*result, line[*i]);
	if (*i + 1 < line_count)
		ft_strcat(*result, "\n");
	free(line[*i]);
	*i += 1;
}

char	*heredoc_set_data(t_pipe *pipe_fd, int line_count, size_t total_length)
{
	char	buffer[1024];
	char	*line[300];
	char	*result;
	size_t	byte_read;
	int		i;

	result = 0;
	byte_read = read((*pipe_fd).read_fd, buffer, sizeof(buffer));
	while (byte_read > 0)
	{
		line[line_count] = ft_strndup(buffer, byte_read - 1);
		total_length += ft_strlen(line[line_count]);
		line_count++;
		byte_read = read((*pipe_fd).read_fd, buffer, sizeof(buffer));
	}
	close((*pipe_fd).read_fd);
	result = (char *)ft_calloc(total_length + line_count, 1);
	i = 0;
	while (i < line_count)
		heredoc_set_line(&result, line, line_count, &i);
	return (result);
}

char	*add_heredoc(char *eof, int *res_status)
{
	t_pipe	pipe_fd;
	pid_t	pid;

	if (pipe((int *)&pipe_fd) == -1)
	{
		perror("sorry. pipe error");
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	signal(SIGINT, SIG_HOLD);
	signal(SIGQUIT, SIG_HOLD);
	if (pid == 0)
		heredoc_input_process(&pipe_fd, eof);
	else
	{
		if (heredoc_parent_handle_error(&pipe_fd, eof, pid, res_status) == 1)
			return (NULL);
		return (heredoc_set_data(&pipe_fd, 0, 0));
	}
	return (NULL);
}
