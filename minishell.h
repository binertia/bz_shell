/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:21:30 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 20:17:51 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>
# include <errno.h>
# include "./libft/libft.h"
# define PROMPT_MSG "\033[36;6mminishell\33[0m:"
# define ARGS_TYPE 0
# define REDIR_TYPE 1
# define CONDITION_TYPE 2
# define PARENT_TYPE 3
# define ERROR_TYPE 4
# define VALID_LLONG 9
# define I_REDIR 0
# define O_REDIR 1
# define APPEN 2
# define HERED 3
# define REDIR_ERR -1
# define PIPE 1
# define OP_OR 2
# define OP_AND 3

typedef struct s_map_list
{
	char				*key;
	char				*value;
	struct s_map_list	*next;
}	t_map_list;

typedef struct s_control_sig
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
}	t_control_sig;

typedef struct s_recursive_token
{
	char	*buf;
	char	*ptr;
	int		utils[2];
}	t_recursive_token;

typedef struct s_redirect
{
	int					type;
	char				*front_fd;
	char				*back_fd;
	char				*heredoc;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_exec
{
	int				run_condition;
	t_list			*cmd;
	t_redirect		*redir;
	struct s_exec	*child;
	struct s_exec	*next;
}	t_exec;

typedef struct s_tok_list
{
	int					token;
	char				*str;
	struct s_tok_list	*next;
	struct s_tok_list	*child;
}	t_tok_list;

typedef struct s_pipe
{
	int	read_fd;
	int	write_fd;
}	t_pipe;

typedef struct s_helper_cmd
{
	char	**all_path;
	int		found;
	int		i;
	char	*path;
}	t_helper_cmd;

typedef struct s_unquote_string
{
	int		i;
	int		j;
	bool	in_double_quote;
	bool	in_single_quote;
	char	*output;
	int		len;
}	t_unquote_string;

volatile int	g_sigint_in;

//handle_allsig/signal_1.c
void			install_term(void);
void			sig_handler(int signal);
void			ft_rl_new(int sig);
void			child_ignore(void);
void			sig_ignore(void);

//handle_allsig/signal_2.c
void			sig_hered(int signal);
void			mod_sig_handle(void (*fn)(int));
void			intstall_term(void);
// void			sigint_handler(int signum, siginfo_t *info, void *ptr);
void			sigint_handler(int signum);
// void			sig_setup_heredoc(void);

//parser/utils/utils.c
char			**ft_split(char const *s, char c);

//parser/make_string.c
int				ft_is_space(int c);
void			manage_string_helper(int *token, int *quote_indicate, int chr);
int				manage_string_space_return(int quote);
char			*manage_string_space(char *src);

//parser/group_token_list.c
t_tok_list		*ft_new_toklist(void);
int				ft_strnum(char *s);

//parser/helper_function/valid_quote_and_recursive_token.c
int				valid_quote(char *str);
void			recursive_token_quote_helper(char **src, char **ptr, int *type);
void			recursive_token_redir_add_char(char **src, int chr_buf, \
			char **buf_ptr, int *count);
void			recursive_token_redir_helper(char **src, char **buf_ptr, \
			int *token);
void			recursive_token_cond_helper(char **src, char **ptr, int *token);

//parser/helper_function/all_check_valid.c
int				check_paren_valid_error(char *str);
void			check_paren_valid_in_quote(char **src_str, int *token);
int				check_paren_valid(char *str);

//parser/all_if.c
int				if_space(char *src, int *condition);
void			if_meet_quote(char **src, char **ptr, int *token, \
				int *condition);
int				if_meet_redir(char **src, char **ptr, int *token, char **buf);
int				if_meet_paren(char **src, int *token, t_tok_list \
				**branch, char **buf);
int				if_meet_condition(char **src, char **ptr, int *token, \
				char **buf);
void			setup_void(char *temp, int root_call);
//parser/recursive_token/recursive_token_1.c
void			setup_recursive_token(char *src, char **buf, char **ptr, \
				t_tok_list **branch);
int				recursive_token_skip_space(char **src, int *utils);
void			recursive_token_send_next(char **src, char **buf, int *token, \
				t_tok_list **branch);
int				recursive_token_setup_loop(char **src, int *condition);
void			recursive_token(char *src, t_tok_list **branch, int root_call, \
				char *temp);

//parser/recursive_token/recursive_token_2.c
void			recursive_token_paren_helper(char **src, int *token, \
				t_tok_list **list);
void			add_list_data(char **s, int token, t_tok_list *list);

//parser/parser/post_parse.c
int				setup_is_parse_able(int *status, bool *in_s_quote, \
				bool *in_d_quote, char *s);
int				is_parse_able(char *s);
char			*i_hope_i_can_use_getpid(void);

//buildin/buildin_cd/cd.c
char			*resolve_absolute_path(char *path, t_map_list *env, \
				char *str_temp);
char			*ft_getcwd_error(void);
char			*resolve_relative_path(char *path, t_map_list *env, \
				char *str_temp);
char			*resolve_up_path(char *path, t_map_list *env);
char			*resolve_path(char *path, t_map_list *env);
int				buildin_cd(t_exec *data, t_map_list *env);

//buildin/buildin_cd/cd_1.c
int				back_to_old_pwd(int *back, char **res_path, t_map_list *env);
int				buildin_cd_manage_return(char **res_path, t_exec *data);
int				ft_cd_root_dir_error(char *home);
int				ft_cd_getcwd_error(char **s);
char			*buildin_cd_add_pwd(t_map_list *env);

//buildin/buildin_export/export_1.c
int				char_valid(char c);
int				handle_delimiter(char *cmd, size_t *i, int *append);
int				check_export_valid(char *cmd);
void			print_export(t_map_list *env);
int				buildin_export(t_map_list *env, char **cmd, int status, \
				int condition);

//buildin/buildin_export/export_2.c
void			append_env(char **add, char **data, t_map_list *env);
int				is_env_dup(t_map_list *env, char **data, int condition);
void			export_one_condition(char **cmd, size_t *j, char **res, \
				t_map_list *env);
void			export_sec_condition(char **cmd, size_t *j, char **res, \
				t_map_list *env);
void			buildin_export_error(char **cmd, int index, int *status);
//buildin/buildin_export/export_3.c
void			setup_value(char **res, size_t temp, char *cmd_temp);
//buildin/buildin_env/env.c
int				buildin_env(t_map_list *env, char **cmd);
void			ft_add_maplist(t_map_list **head, char **src);
t_map_list		*get_env_list(char **env);
t_map_list		*ft_new_mapnode(char *key, char *value);
t_map_list		*copy_map_list(t_map_list *head);
///
///
///
//
///
///
///
///
char			*ft_getenv(char *s, t_map_list *env, int status);
void			ft_free_chrarr(char **arr);
void			ft_add_maplist(t_map_list **head, char **src);
char			**get_cmd_arr(t_list *cmd, t_map_list *env, int status);
int				get_status(int status);
t_list			*get_replaced(char *str, t_map_list *env, int status);
int				is_parse_able(char *s);
char			*replace_addback(char *str, size_t *index, t_map_list *env, \
				int status);
void			unquote_realloc_str(char **str);
void			ft_free_tok_list(t_tok_list *head);
t_tok_list		*group_per_exec(char *src);
void			replace_str_moving_ptr(t_list **temp, size_t *len);
void			replace_str(char **str, t_map_list *env, int status);
t_map_list		*copy_map_list(t_map_list *head);
void			execute_recursive(t_exec *cmd, int *status, \
			t_map_list **env, int child);
char			*ft_itoa(int n);
void			ft_free_map_list(t_map_list *env);
void			clean_unused_cmd(t_exec **head, char **input);
///
//
//
//
///
///
///
///
///
///
///
//buildin/buildin_exit/exit_1.c
int				ft_strnum_exit(char *s);
long long		ft_atoll(char *s);
int				over_llong_minus(char *s);
int				over_llong_plus(char *s);
int				handle_over_llong(char *s);

//buildin/buildin_exit/exit.c
int				buildin_exit_args_err(int *status);
void			buildin_exit_alp_arg(char **cmd, int *status);
int				buildin_exit(char **cmd, int *status);

//buildin/buildin_unset/unset.c
void			ft_node_cmp_remove(t_map_list **env, char *str);
int				check_valid_unset(char *s);
int				buildin_unset(t_map_list **env, char **cmd);

//buildin/run_buildin.c
void			run_buildin_cmd(t_exec *data, int *status, \
				t_map_list **env, char **cmd);
int				check_buildin(char *cmd);

//buildin/buildin_echo.c
int				buildin_echo(char **cmd);

//buildin/buildin_pwd.c
int				buildin_pwd(t_map_list *head);

//execute/utils/utils_0.c
t_exec			*make_new_exec(void);
int				get_type_size(int type, t_tok_list *data);
void			add_exec_args(t_exec *head, t_tok_list *data, int type);
t_redirect		*ft_new_redir(void);
int				ft_atoi_strict(char *s);

//execute/mange_fd/get_fd_1.c
char			*get_back_fd(t_tok_list **data);
void			add_exec_redir(t_exec *head, t_tok_list **data);
void			ft_new_list_addback(t_list **head, char *s);
int				get_condition(char *data);

//execute/mange_fd/get_fd.c
char			*get_front_fd(char *s);
int				get_type_redir_case(char *s, int i);
int				get_type_redir(char *s);
int				valid_numb_str(char *s);
char			*get_back_fd_from_next_node(t_tok_list **data, char *s);

//execute/mange_fd/get_execu_data.c
void			get_exec_data(t_tok_list *data, t_exec **head);
int				recheck_redir(t_tok_list *list);
int				check_child(char *s);
int				check_redir_valid_error(int redir);
void			move_ptr_in_quote(int *token, char **str);

//execute/mange_fd/check_redir_fd.c
void			skip_redir(char **str, int *count, int *redir);
int				check_redir_valid(char *str);
int				check_redir_valid_error(int redir);
void			move_ptr_in_quote(int *token, char **str);

//execute/mange_fd/check_redir_fd.c
void			heredoc_input_process(t_pipe *pipe_fd, char *eof);
int				heredoc_parent_handle_error(t_pipe *pipe_fd, char *eof, \
				pid_t pid, int *res_status);
void			heredoc_set_line(char **result, char **line, \
				int line_count, int *i);
char			*heredoc_set_data(t_pipe *pipe_fd, int line_count, \
				size_t total_length);
char			*add_heredoc(char *eof, int *res_status);

//execute/mange_fd/get_heredoc/check_redir_fd.c
void			heredoc_input_process(t_pipe *pipe_fd, char *eof);
int				heredoc_parent_handle_error(t_pipe *pipe_fd, \
				char *eof, pid_t pid, int *res_status);
void			heredoc_set_line(char **result, char **line, \
				int line_count, int *i);
char			*heredoc_set_data(t_pipe *pipe_fd, int line_count, \
				size_t total_length);
char			*add_heredoc(char *eof, int *res_status);

//execute/mange_fd/get_heredoc/get_heredoc.c
int				get_heredoc(t_exec *head, t_map_list *env, int *status);

//execute/mange_fd/get_heredoc/here_doc_2.c
int				setup_replace_hered_str(char **str, t_map_list *env, \
				int status, t_list **head);
void			replace_hered_str(char **str, t_map_list *env, int status);
int				check_parsing_eof(char **eof, t_redirect **temp, \
				int *status, t_map_list *env);
void			get_eof_from_next_args(t_exec *list, char **eof);
int				get_heredoc_loop(t_exec *exec_temp, int *status, \
				t_map_list *env);
int				setup_replace_hered_str(char **str, t_map_list *env, \
				int status, t_list **head);
void			ft_replace_hered_set_free(char **str, \
				t_list *for_free, char *res);
//execute/mange_fd/get_heredoc/here_doc_1.c
void			setup_search_replace(bool *s_quote, bool *d_quote, size_t *i);
void			replace_addback_manage(char *str, size_t *i, bool *in_quote);
void			update_and_free(t_list **res, char **temp, \
				char **str, size_t *i);
int				loop_search_replace(char **str, \
				t_map_list *env, int status, t_list **res);
t_list			*get_heredoc_replaced(char *str, t_map_list *env, int status);
//execute/mange_fd/get_heredoc/here_doc_3.c
void			setup_search_replace(bool *s_quote, bool *d_quote, size_t *i);
t_list			*get_heredoc_replaced(char *str, t_map_list *env, int status);
//execute/make_sure_parser/check_1.c
int				dup_or_nullafter_condition(t_tok_list *list);
int				bad_condition_child(t_tok_list *list);
int				setup_buf_check_condition(t_tok_list *list, int *buf);
int				fake_condition(t_tok_list *list);
int				setup_and_run_check_for_child(t_tok_list *list, int *buf);

//execute/make_sure_parser/check_2.c
int				no_file_name_or_redir_num(t_exec *node);
int				check_redir_valid_exec(t_exec *node);
int				check_extra_redir_errone(t_tok_list *temp_list);
int				check_extra_redir_errtwo(t_tok_list *temp_list);
int				check_extra_redir_errthree(t_tok_list *temp_list, \
				char *str, int index);

//execute/make_sure_parser/check_3.c
int				check_extra_redir_errfour(t_tok_list *temp_list, \
				t_tok_list *list);
int				check_extra_redir_errfive(t_tok_list *temp_list, \
				t_tok_list *list);
int				check_extra_redir_errsix(t_tok_list *temp_list, \
				t_tok_list *list);
int				sorry_i_no_have_name_left(t_tok_list *temp_list, \
				t_tok_list *list);
int				check_all_condition(t_tok_list *temp_list, \
				t_tok_list *list, int *i);

//execute/make_sure_parser/check_4.c
int				check_extra_redir(t_tok_list *list);
int				check_child_valid(t_tok_list *head);
int				check_error_sticky_child(t_exec *head);
int				child_valid_on_child(t_exec *head);
int				check_child_valid_exec(t_exec *head);

//execute/make_sure_parser/check_5.c
int				child_and_condition_err(t_tok_list *head);
int				check_child_condition_valid(t_tok_list *head, int lock);
int				check_raw_str(char *str);
int				check_token_list(t_tok_list *list);
int				check_addition_exec(t_exec *head);

//execute/make_sure_parser/check_6.c
int				check_condition_valid(t_tok_list *list);

//execute/make_sure_parser/free.c
void			ft_free_cmd_list(t_list *head);
void			ft_free_redir_list(t_redirect *head);
void			ft_free_exec(t_exec *head);

//parser/parser.c
t_exec			*parser(char *raw_data, t_map_list *env, int *status);
t_tok_list		*group_per_exec(char *src);
int				valid_raw_data(t_tok_list *data, int *error);

//execute/execute_parser/exe_parser_0.c
int				ft_redir_len(t_redirect *head);
int				ft_dup2(int f_redir, int b_redir);

//execute/execute_parser/exe_parser_1.c
int				run_redir_in(char *file_name, int f_redir);
int				check_file_avaiable(char *file_name );
int				run_redir_out_filename(char *file_name, int b_redir);
int				run_solo_redir_out(char *file_name, int f_redir, int b_redir);
int				try_run_ampersand_appen(int fd);

//execute/execute_parser/exe_parser_2.c
int				run_redir_appen(char *file_name, int f_redir);
int				run_redir_heredoc(char **file_name, t_redirect *redir);
int				manage_out_redir(char *file_name, int f_redir, int b_redir);
int				start_run_redir(t_redirect **redir, \
				char **file_name, int f_redir, int b_redir);
int				setup_run_redir(char **file_name, \
				t_redirect **redir, t_exec *data);

//execute/execute_parser/exe_parser_3.c
int				run_redir(t_exec *data, t_map_list *env, \
				int status, int f_redir);
void			setup_getcmd(size_t *count, t_list **temp, int *i, t_list *cmd);
void			*get_cmd_arr_free_return(char **res);
char			**get_cmd_arr(t_list *cmd, t_map_list *env, int status);
size_t			ft_map_len(t_map_list *env);

//execute/execute_parser/exe_parser_4.c
size_t			ft_env_len(t_map_list *env);
char			**comply_env(t_map_list *env);
void			ft_free_chrarr(char **arr);

//execute/execute_parser/exe_run_dir.c
void			setup_redir(t_redirect *redir, int *f_redir, \
				int *b_redir, int *check);
void			add_case_ampersand(t_redirect *redir, \
				int *b_redir, char **file_name, int *check);
int				bad_dollar_sign_usage(t_redirect *redir);
void			unquote_and_add_target_fd_ref(t_redirect *redir, \
				int *b_redir, char **file_name, int *check);
void			getfd_ref_from_next_args(t_exec **data, t_map_list *env, \
				int *status, char **file_name);

//execute/execve/exeve_0.c
void			execve_child(char **cmd_path, char **env_temp);
void			execve_wait_for_child(pid_t *pid, int *return_status, \
				char **cmd, char **env);
int				execve_in_child(int *return_status, \
				char **cmd_path, char **env_temp);

//execute/execve/exeve_1.c
void			setup_check_placeholder(int *checker, \
				bool *in_s_quote, bool *in_d_quote);
void			check_for_placeholder(int *checker, char *str);
int				manage_redir(t_exec *data, int *status, t_map_list *env);
void			ft_free_chrarr_with_ptr(char **arr);
int				no_cmd_to_run(int *checker, int *status, char **cmd);			
//execute/execve/exeve_2.c
int				manage_run_cmd(t_exec *data, int *status, t_map_list **env);
int				run_cmd(t_exec *data, int *status, t_map_list **env);
void			setup_start_pipe(pid_t *pid, int *pipefd, \
				int *new_status, int *status);
void			manage_first_pipe_child(int *pipefd, t_exec *data, \
				int *new_status, t_map_list **env);
int				manage_parent_waitchild(int *status, int *pid, int *pipefd);

//execute/execve/exeve_3.c
int				run_normal_cmd(char **env_temp, int *status, \
				t_map_list *env, char **cmd_path);

//execute/execve/exeve_4.c
void			start_pipe(t_exec *data, int *status, \
				t_map_list *env, int *std);

//execute/execve/exeve_5.c
int				execute_pipe_parent(t_exec *cmd, pid_t *parent, \
				t_map_list **temp, int *pipefd);
void			execute_pipe_child(t_exec *cmd, int *status, t_map_list **env);
void			execute_solo_child(t_exec *cmd, t_map_list *env, int *status);
void			execute_next_cmd(t_exec *cmd, int *status, \
				t_map_list **env, int *std);
int				setup_execute(t_exec *cmd, int child);
int				manage_parent_waitchild(int *status, int *pid, int *pipefd);
int				manage_parent_waitchild(int *status, \
				int *pid, int *pipefd);
void			setup_parent_waitchild(int *pipefd, \
				int *paren_status, int *pid);
//execute/utils/utils_1.c
void			ft_fflush(int *std, int is_dup, int is_close, int is_flush);
void			set_dup_fd(int fd_close, int fd_open, int f_redir);
//utils/utils_0.c
char			*ft_getenv(char *s, t_map_list *env, int status);
int				ft_strnum_only(char *s);
void			setup_replace_addback(char *str, size_t *index, \
				char **buf, char **ptr);
char			*replace_addback_return(char **buf, t_map_list *env, \
				int status);
char			*replace_addback(char *str, size_t *index, \
				t_map_list *env, int status);

//utils/utils_2.c
char			*unquote_string(char *input);
void			unquote_realloc_str(char **str);
void			ft_free_list(t_list *head);
void			replace_str_moving_ptr(t_list **temp, size_t *len);

//utils/utils_3.c
void			replace_str(char **str, t_map_list *env, int status);
void			setup(t_map_list *env);
void			set_add_history(char *input, t_map_list **env, \
				int *g_status, t_exec **head);
int				hook_eof(char *input);
void			hook_sigint(t_exec **head, t_map_list **env);

//utils/utils_3.c
int				ft_strcmp(char *s1, char *s2);
char			*ft_strndup(const char *s, size_t n);
size_t			ft_strnlen(const char *s, size_t maxlen);
char			*ft_strstr(const char *haystack, const char *needle);
//utils/utils_5.c
void			ft_strcat(char *dst, char *src);
char			*ft_strcpy(char *dst, char *src);
void			set_temp_head(t_list **head_temp, t_list *head, t_list **temp);
void			print_header(t_map_list *env);

//execute/utils/utils_free.c
void			ft_free_map_list(t_map_list *env);
//execute/execute_recursive.c
void			execute_recursive(t_exec *cmd, int *status, \
				t_map_list **env, int child);

//minishell.c
int				minishell(t_map_list *env);
void			ft_stack_std(int *arr);
int				run_line(char *raw_data, t_map_list **env, \
				int *g_status, t_exec **cmd);

//backend
void			set_hidden(t_map_list *env, char *hidden_pwd);
char			*set_hidden_fallback_pwd(void);
int				no_sufficient_data_to_run(void);
char			*set_hidden_fallback_pwd(void);

//newly added
char			*ft_strcpy(char *dst, char	*src);
// char			*ft_strcat(char *dst, char *src);
void			export_pwd_oldpwd(char *res_path, t_map_list *env, \
				char *dir_path, char *target);
void			update_pwd_str(char *resolved_path, t_map_list *env);
void			ps_export_back_old_pwd(char *old_path, t_map_list *env);
int				extend_run_solo_redir_out(int f_redir, int fd, char *file_name);
int				run_redir_heredoc(char **file_name, t_redirect *redir);
int				bad_filename(t_redirect *redir, char **file_name);
int				try_run_absolute_cmd(char **cmd_path, \
				int *status, char **all_path);
int				check_absolute_command(char **cmd_path, int *status);
int				get_cmd_state(int *found, char **cmd_path, \
				char **all_path, int i);
int				make_full_cmd_path(int found, char **all_path, \
				char **cmd_path, int i);
int				command_not_found_err(char **all_path, char **cmd_path);
char			*get_full_cmd_path(char *path, char **cmd);
int				setup_buildin_export(int *condition, size_t *j, \
				char **res, char **cmd);
#endif