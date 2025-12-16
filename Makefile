# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/02 23:20:38 by kesaitou          #+#    #+#              #
#    Updated: 2025/12/16 09:26:02 by natakaha         ###   ########.fr        #
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
			srcs/builtin_cmd/cmd_utils_info.c\
			srcs/execution/exec_utils1_pid.c\
			srcs/execution/exec_utils2_error.c\
			srcs/execution/exec_utils3_pipe.c\
			srcs/execution/exec1_operate.c\
			srcs/execution/exec2_cmd.c\
			srcs/execution/exec3_pipe.c\
			srcs/execution/exec4_redirect.c\
			srcs/lexer/charlist.c\
			srcs/lexer/lexer_utils.c\
			srcs/lexer/lexer.c\
			srcs/lexer/token_list_utils.c\
			srcs/parser/utils1_make_tree.c\
			srcs/parser/utils2_redirect.c\
			srcs/parser/utilas3_parse.c\
			srcs/parser/getsize.c\
			srcs/parser/parse.c\
			srcs/main/main.c\
			srcs/main/signal.c\
			srcs/main/tester.c\


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
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all


.PHONY: all clean fclean re