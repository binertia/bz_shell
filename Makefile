NAME		:=	minishell
CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -I/usr/local/opt/readline/include
#-g -fsanitize=address
RFLAGS		:=	-L/usr/local/opt/readline/lib -lreadline
# CFLAGS		:=	-I/opt/homebrew/opt/readline/include
# RFLAGS		:=	-L/opt/homebrew/opt/readline/lib -lreadline
INCLUDES	:=	minishell.h
LIBFT		:=	./libft/libft.a

SRC	:=	main.c\
		backend/hidden_var.c\
		handle_allsig/signal_1.c\
		handle_allsig/signal_2.c\
		handle_allsig/signal_3.c\
		handle_allsig/signal_4.c\
		parser/parser.c\
		parser/post_parse.c\
		parser/all_if.c\
		parser/group_token_list.c\
		parser/utils/utils.c\
		parser/make_string.c\
		parser/helper1.c\
		parser/helper_function/valid_quote_and_recursive_token.c\
		parser/helper_function/all_check_valid.c\
		parser/recursive_token/helper.c\
		parser/recursive_token/recursive_token_1.c\
		parser/recursive_token/recursive_token_2.c\
		buildin/buildin_cd/cd.c\
		buildin/buildin_cd/cd_1.c\
		buildin/buildin_cd/cd_helper.c\
		buildin/buildin_cd/cd_2.c\
		buildin/buildin_export/export_1.c\
		buildin/buildin_export/export_2.c\
		buildin/buildin_export/export_helper.c\
		buildin/buildin_export/export_3.c\
		buildin/buildin_export/export_4.c\
		buildin/buildin_env/env.c\
		buildin/buildin_exit/exit.c\
		buildin/buildin_exit/exit_1.c\
		buildin/buildin_unset/unset.c\
		buildin/run_buildin.c\
		buildin/buildin_echo.c\
		buildin/buildin_pwd.c\
		execute/utils/utils_0.c\
		execute/mange_fd/get_fd_1.c\
		execute/mange_fd/get_fd.c\
		execute/mange_fd/get_execu_data.c\
		execute/mange_fd/check_redir_fd.c\
		execute/mange_fd/get_heredoc/here_doc.c\
		execute/mange_fd/get_heredoc/get_heredoc.c\
		execute/mange_fd/get_heredoc/here_doc_3.c\
		execute/mange_fd/get_heredoc/here_doc_2.c\
		execute/mange_fd/get_heredoc/here_doc_1.c\
		execute/make_sure_parser/check_1.c\
		execute/make_sure_parser/check_2.c\
		execute/make_sure_parser/check_3.c\
		execute/make_sure_parser/check_4.c\
		execute/make_sure_parser/check_5.c\
		execute/make_sure_parser/check_6.c\
		execute/make_sure_parser/free.c\
		execute/execute_parser/exe_parser_0.c\
		execute/execute_parser/exe_run_dir.c\
		execute/execute_parser/exe_run_dir_1.c\
		execute/execute_parser/exe_run_dir_2.c\
		execute/execute_parser/exe_run_dir_3.c\
		execute/execute_parser/exe_run_dir_4.c\
		execute/execute_parser/exe_run_dir_5.c\
		execute/execve/exeve_0.c\
		execute/execve/exeve_1.c\
		execute/execve/exeve_2.c\
		execute/execve/exeve_3.c\
		execute/execve/exeve_4.c\
		execute/execve/exeve_5.c\
		execute/execve/execve_6.c\
		execute/execve/execve_7.c\
		execute/execute_recursive.c\
		execute/redirect/redir_helper1.c\
		execute/utils/utils_1.c\
		utils/utils_0.c\
		utils/utils_1.c\
		utils/utils_2.c\
		utils/utils_3.c\
		utils/utils_4.c\
		utils/utils_5.c\
		utils/utils_free.c\
		minishell.c

OBJ 	:=	$(SRC:.c=.o)

all: 	$(NAME)

$(NAME) : $(OBJ) $(INCLUDES)
	$(MAKE) -C libft
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(RFLAGS) -o $(NAME)


clean:
		rm -rf $(OBJ)

fclean: clean
		$(MAKE) -C libft fclean
		rm -rf $(NAME)

re : 	fclean all

.PHONY: all clean fclean re
