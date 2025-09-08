# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 23:11:53 by manuelma          #+#    #+#              #
#    Updated: 2025/09/08 23:33:46 by manuelma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= get_next_line.c get_next_line_utils.c
OBJS		= $(SRCS:.c=.o)
CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -I.
NAME		= get_next_line.a

all:		$(NAME)

$(NAME):	$(OBJS)
			@ar rcs $(NAME) $(OBJS)
			@printf "get_next_line compiled succesfully !\n"

$(OBJS)		: %.o: %.c
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(RM) $(OBJS)
			@printf "Removed all object files from get_next_line !\n"

fclean:		clean
			@$(RM) $(NAME)
			@printf "Removed executable file from get_next_line !\n"

clean_exec:		
			@$(RM) $(NAME)
			@printf "Removed executable file from get_next_line !\n"

re:			fclean $(NAME)

.PHONY:		all clean fclean clean_exec re bonus
