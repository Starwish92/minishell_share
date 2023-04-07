# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youngjpa <youngjpa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 13:03:55 by youngjpa          #+#    #+#              #
#    Updated: 2023/04/07 17:46:26 by youngjpa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS		=	minishell.c				 \
				./parse/argc_checker.c 	 \
				./parse/ft_split_arg.c   \
				./parse/join_string.c    \
				./parse/parse.c 		 \
				./parse/quotes_setting.c \
				./parse/tokenize_util.c  \
				./parse/tokenize.c		 \
				./utillites/exit_errono.c \
				./utillites/file_open_check.c\
				./utillites/init_and_free.c \
				./utillites/signal_handle.c \
				./utillites/systemcall1.c \
				./utillites/systemcall2.c \
				./utillites/util1.c \
				./utillites/util2.c \
				./utillites/util3.c \
				./utillites/util4.c \
				./utillites/util5.c \

OBJS		= $(SRCS:%.c=%.o)

CC = gcc $(DEBUG)
CFLAGS = -Werror -Wall -Wextra
# SAN = -fsanitize=address -g3
DEBUG = -g
READLINE_LIB 	= -lreadline -L/opt/homebrew/opt/readline/lib
READLINE_INC	= -I/opt/homebrew/opt/readline/include
# READLINE_LIB 	= -lreadline -L${HOME}/.brew/opt/readline/lib
# READLINE_INC	= -I${HOME}/.brew/opt/readline/include

FT_DIR	= ./libft
FT 	= ft

all			:	$(NAME)

$(NAME)		:	$(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(READLINE_LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean		:
		rm -f $(OBJS)

fclean		:	clean
		rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re bonus
