# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 23:11:53 by manuelma          #+#    #+#              #
#    Updated: 2025/09/08 23:56:14 by manuelma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Color_Off='\033[0m'
IGreen='\033[0;92m'
IRed='\033[0;91m'

SRCS		= get_next_line.c get_next_line_utils.c
OBJS		= $(SRCS:.c=.o)
CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -I.
NAME		= get_next_line.a

all:		$(NAME)

$(NAME):	$(OBJS)
			@ar rcs $(NAME) $(OBJS)
			@printf $(IGreen)
			@printf "get_next_line compiled succesfully !$(RESET)\n"

$(OBJS)		: %.o: %.c
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(RM) $(OBJS)
			@printf $(IRed)
			@printf "Removed all object files from get_next_line !$(RESET)\n"

fclean:		clean
			@$(RM) $(NAME)
			@printf $(IRed)
			@printf "Removed executable file from get_next_line !$(RESET)\n"

clean_exec:		
			@$(RM) $(NAME)
			@printf $(IRed)
			@printf "Removed executable file from get_next_line !$(RESET)\n"

re:			fclean $(NAME)

.PHONY:		all clean fclean clean_exec re bonus
