# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/02 23:20:38 by kesaitou          #+#    #+#              #
#    Updated: 2026/01/21 05:54:26 by natakaha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -g -O0 -Wall -Werror -Wextra

INCS = includes
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

LIBDIR = $(LIBFTDIR)
LDFLAGS = -L $(LIBDIR)
LDLIBS = -lft -lreadline

MAND_SRCS = srcs/builtin_cmd/cmd_cd.c\
			srcs/builtin_cmd/cmd_echo.c\
			srcs/builtin_cmd/cmd_env.c\
			srcs/builtin_cmd/cmd_exit.c\
			srcs/builtin_cmd/cmd_export.c\
			srcs/builtin_cmd/cmd_pwd.c\
			srcs/builtin_cmd/cmd_unset.c\
			srcs/builtin_cmd/cmd_utils_env.c\
			srcs/execution/exec1_operate.c\
			srcs/execution/exec2_logical.c\
			srcs/execution/exec3_execve.c\
			srcs/execution/exec4_builtin.c\
			srcs/execution/exec5_env.c\
			srcs/execution/exec6_redirect.c\
			srcs/execution/utils1_pid.c\
			srcs/execution/utils2_redirect_error.c\
			srcs/execution/utils3_pipe.c\
			srcs/execution/utils4_find_path.c\
			srcs/expander/expand1_env.c\
			srcs/expander/expand2_wildcard.c\
			srcs/expander/expand3_expander.c\
			srcs/expander/expand4_ifs.c\
			srcs/expander/utils1.c\
			srcs/expander/utils2_search_file.c\
			srcs/expander/utils3_ifs.c\
			srcs/lexer/lexer1_tokenize.c\
			srcs/lexer/utils1_tlist1.c\
			srcs/lexer/utils1_tlist2.c\
			srcs/lexer/utils3_judge.c\
			srcs/main/main.c\
			srcs/main/utils1_exit_code.c\
			srcs/main/utils2_signal.c\
			srcs/main/utils3.c\
			srcs/parser/parse1_cmd.c\
			srcs/parser/parse2_pipe.c\
			srcs/parser/parse3_logical.c\
			srcs/parser/parse4_parser.c\
			srcs/parser/utils1_tree.c\
			srcs/parser/utils2_parse.c\
			srcs/parser/utils3_is.c\
			srcs/parser/utils4_arglist.c\
			srcs/parser/utils5_heardoc.c\
			srcs/tester/print_.c\

MAND_OBJS = $(MAND_SRCS:.c=.o)


all : $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(NAME):$(MAND_OBJS) $(LIBFT)
	$(CC) $(MAND_OBJS) $(LDFLAGS) $(LDLIBS) -g -O0 -o $(NAME)

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
