# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 16:41:17 by manuelma          #+#    #+#              #
#    Updated: 2025/09/30 19:29:11 by manuelma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include mk/print_ascii_art.mk

NAME				= cub3d
CC					= cc
CFLAGS				= -Wall -Wextra -Werror -g
OBJ_DIR				= objs

SRCS_DIR			= src/
M_PARSE_DIR			= $(SRCS_DIR)map_parsing/
M_CHECK_DIR			= $(SRCS_DIR)map_checking/

SRCS_MAIN			= main.c debug.c string_utils.c

SRCS_M_PARSE		= color_utils.c  \
					map_parser.c  \
					param_parser.c  \
					parsing_utils.c  \
					read_file.c

SRCS_M_CHECK		= main_checker.c

SRCS				= $(addprefix $(SRCS_DIR), $(SRCS_MAIN)) \
					  $(addprefix $(M_PARSE_DIR), $(SRCS_M_PARSE)) \
					  $(addprefix $(M_CHECK_DIR), $(SRCS_M_CHECK))

OBJS				= $(SRCS:%.c=$(OBJ_DIR)/%.o)
PROJ_INC			= -I$(SRCS_DIR) -I$(M_PARSE_DIR)
LIBFT_PATH			= libft
LIBFT				= $(LIBFT_PATH)/libft.a
LIBFT_INC			= -I$(LIBFT_PATH)
GNL_PATH			= get_next_line
GNL					= $(GNL_PATH)/get_next_line.a
GNL_INC				= -I$(GNL_PATH)

all: $(LIBFT) $(GNL) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GNL) -o $(NAME)
	@printf $(IGreen)
	@printf "Cub3d compiled successfully!$(RESET)\n"
	$(call PRINT_WORD,$(NAME),ICyan)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(PROJ_INC) $(LIBFT_INC) $(GNL_INC) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory

$(GNL):
	@$(MAKE) -C $(GNL_PATH) --no-print-directory

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory
	@$(MAKE) -C $(GNL_PATH) clean --no-print-directory
	@printf $(IRed)
	@printf "Removed all object files from cub3d!.$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory || \
	 $(MAKE) -C $(LIBFT_PATH) clean_exec --no-print-directory
	@$(MAKE) -C $(GNL_PATH) fclean --no-print-directory || true
	@printf $(IRed)
	@printf "Removed executable and libraries.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re

