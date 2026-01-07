# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/02 23:20:38 by kesaitou          #+#    #+#              #
#    Updated: 2026/01/08 03:56:36 by kesaitou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -g -Wall -Werror -Wextra

INCS = includes
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

LIBDIR = $(LIBFTDIR)
LDFLAGS = -L $(LIBDIR)
LDLIBS = -lft -lreadline

MAND_SRCS = srcs/builtin_cmd/cmd_echo.c\
			srcs/builtin_cmd/cmd_pwd.c\
			srcs/builtin_cmd/cmd_cd.c\
			srcs/builtin_cmd/cmd_export.c\
			srcs/builtin_cmd/cmd_env.c\
			srcs/builtin_cmd/cmd_exit.c\
			srcs/builtin_cmd/cmd_utils_info.c\
			srcs/builtin_cmd/cmd_utils.c\
			srcs/execution/exec_utils1_pid.c\
			srcs/execution/exec_utils2_error.c\
			srcs/execution/exec_utils3_pipe.c\
			srcs/execution/exec_utils4_env.c\
			srcs/execution/exec1_operate.c\
			srcs/execution/exec2_cmd.c\
			srcs/execution/exec3_logical.c\
			srcs/execution/exec4_redirect.c\
			srcs/lexer/lexer1_tokenize.c\
			srcs/lexer/lexer2_manage_states.c\
			srcs/lexer/lexer3_manage_operaters.c\
			srcs/lexer/lexer4_subtoken.c\
			srcs/lexer/lexer_utils1_token.c\
			srcs/lexer/lexer_utils2_tlist.c\
			srcs/lexer/lexer_utils3_clist.c\
			srcs/lexer/lexer_utils4_is.c\
			srcs/parser/utils1_make_tree.c\
			srcs/parser/utils3_parse.c\
			srcs/parser/utils4_heardoc.c\
			srcs/parser/utils5_is_.c\
			srcs/parser/utils7_arglist.c\
			srcs/parser/parse.c\
			srcs/parser/parse_cmd.c\
			srcs/expander/expand1_variables_expantion.c\
			srcs/expander/expand3_path_name_expantion.c\
			srcs/expander/utils1_.c\
			srcs/expander/utils2_match_char.c\
			srcs/main/main.c\
			srcs/main/signal.c\
			srcs/main/error.c\

MAND_OBJS = $(MAND_SRCS:.c=.o)


all : $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(NAME):$(MAND_OBJS) $(LIBFT)
	$(CC) $(MAND_OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

bonus: all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(MAND_OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all


.PHONY: all clean fclean re