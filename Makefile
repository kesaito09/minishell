# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/02 23:20:38 by kesaitou          #+#    #+#              #
#    Updated: 2026/04/29 21:59:31 by natakaha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra

INCS = includes
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

READLINE_PREFIX := $(shell brew --prefix readline 2>/dev/null)
ifneq ($(READLINE_PREFIX),)
	CFLAGS += -I$(READLINE_PREFIX)/include
	LDFLAGS_RL = -L$(READLINE_PREFIX)/lib
endif

LIBDIR = $(LIBFTDIR)
LDFLAGS = -L $(LIBDIR) $(LDFLAGS_RL)
LDLIBS = -lft -lreadline

MAND_SRCS = srcs/builtin_cmd/cmd_cd.c\
			srcs/builtin_cmd/cmd_echo.c\
			srcs/builtin_cmd/cmd_env.c\
			srcs/builtin_cmd/cmd_exit.c\
			srcs/builtin_cmd/cmd_export.c\
			srcs/builtin_cmd/cmd_pwd.c\
			srcs/builtin_cmd/cmd_unset.c\
			srcs/builtin_cmd/env_helpers.c\
			srcs/execution/exec_dispatch.c\
			srcs/execution/exec_logical.c\
			srcs/execution/exec_execve.c\
			srcs/execution/exec_builtin.c\
			srcs/execution/redirect.c\
			srcs/execution/pid_list.c\
			srcs/execution/error_check.c\
			srcs/execution/fd_manage.c\
			srcs/execution/env_filter.c\
			srcs/execution/path_search.c\
			srcs/execution/path_split.c\
			srcs/execution/child_helpers.c\
			srcs/execution/builtin_helpers.c\
			srcs/execution/heardoc.c\
			srcs/expander/env_expand.c\
			srcs/expander/wildcard.c\
			srcs/expander/expander.c\
			srcs/expander/string_join.c\
			srcs/expander/glob_match.c\
			srcs/lexer/lexer1_tokenize.c\
			srcs/lexer/utils1_tlist1.c\
			srcs/lexer/utils1_tlist2.c\
			srcs/lexer/utils1_tlist3.c\
			srcs/lexer/utils4_judge.c\
			srcs/main/main.c\
			srcs/main/fatal_exit.c\
			srcs/main/env_special.c\
			srcs/main/signal.c\
			srcs/main/init.c\
			srcs/main/input.c\
			srcs/main/logo_main.c\
			srcs/main/logo_fire.c\
			srcs/parser/parse1_cmd.c\
			srcs/parser/parse2_pipe.c\
			srcs/parser/parse3_logical.c\
			srcs/parser/parse4_parser.c\
			srcs/parser/utils1_tree.c\
			srcs/parser/utils2_parse.c\
			srcs/parser/utils3_is.c\
			srcs/parser/utils4_arglist.c\

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
