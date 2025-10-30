# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 16:41:17 by manuelma          #+#    #+#              #
#    Updated: 2025/10/27 15:35:27 by manuelma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include mk/print_ascii_art.mk

NAME				= cub3D
NAME_BONUS			= $(NAME)_bonus
CC					= cc
CFLAGS				= -Wall -Wextra -Werror -g
OBJ_DIR				= objs

MLX_DIR             = ../minilibx
MLX_LIB             = $(MLX_DIR)/libmlx.a
MLX_FLAGS           = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
SRCS_DIR			= src/
M_PARSE_DIR			= $(SRCS_DIR)map_parsing/
M_CHECK_DIR			= $(SRCS_DIR)map_checking/
GRAPHICS_DIR		= $(SRCS_DIR)graphics/

SRCS_MAIN_COMMON    = string_utils.c \
					strs_dup.c \
					move.c \
					init.c \
					key_handler.c

SRCS_M_PARSE		= color_utils.c  \
					map_parser.c  \
					param_parser.c  \
					parsing_utils.c  \
					read_file.c	\
					map_rectangular.c

SRCS_M_CHECK		= main_checker.c map_check_utils.c

SRCS_GRAPHICS		= init_ray.c pixel_image.c render.c texture.c

SRCS_COMMON			= $(addprefix $(SRCS_DIR), $(SRCS_MAIN_COMMON)) \
					  $(addprefix $(M_PARSE_DIR), $(SRCS_M_PARSE)) \
					  $(addprefix $(M_CHECK_DIR), $(SRCS_M_CHECK)) \
					  $(addprefix $(GRAPHICS_DIR), $(SRCS_GRAPHICS))

SRCS_MANDATORY 		= $(addprefix $(SRCS_DIR), main.c) $(SRCS_COMMON)
OBJS_MANDATORY 		= $(SRCS_MANDATORY:%.c=$(OBJ_DIR)/%.o)

SRCS_BONUS 			= $(addprefix $(SRCS_DIR), main_bonus.c minimap_bonus.c) $(SRCS_COMMON)
OBJS_BONUS 			= $(SRCS_BONUS:%.c=$(OBJ_DIR)/%.o)

PROJ_INC			= -I$(SRCS_DIR) -I$(M_PARSE_DIR)
LIBFT_PATH			= libft
LIBFT				= $(LIBFT_PATH)/libft.a
LIBFT_INC			= -I$(LIBFT_PATH)
GNL_PATH			= get_next_line
GNL					= $(GNL_PATH)/get_next_line.a
GNL_INC				= -I$(GNL_PATH)

all: $(LIBFT) $(MLX_LIB) $(GNL) $(NAME)

$(NAME): $(OBJS_MANDATORY)
	@$(CC) $(CFLAGS) -fsanitize=address -g $(OBJS_MANDATORY) $(LIBFT) $(GNL) $(MLX_FLAGS) -o $(NAME)
	@printf $(IGreen)
	@printf "Cub3d compiled successfully!$(RESET)\n"
	$(call PRINT_WORD,$(NAME),ICyan)

bonus: $(LIBFT) $(MLX_LIB) $(GNL) $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) -fsanitize=address -g $(OBJS_BONUS) $(LIBFT) $(GNL) $(MLX_FLAGS) -o $(NAME_BONUS)
	@printf $(IGreen)
	@printf "Cub3d BONUS compiled successfully!$(RESET)\n"
	$(call PRINT_WORD,$(NAME_BONUS),ICyan)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(PROJ_INC) $(LIBFT_INC) $(GNL_INC) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(GNL):
	@$(MAKE) -C $(GNL_PATH) --no-print-directory

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory
	@$(MAKE) -C $(GNL_PATH) clean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean
	@printf $(IRed)
	@printf "Removed all object files from cub3d!.$(RESET)\n"

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory || \
	 $(MAKE) -C $(LIBFT_PATH) clean_exec --no-print-directory
	@$(MAKE) -C $(GNL_PATH) fclean --no-print-directory || true
	@printf $(IRed)
	@printf "Removed executable and libraries.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re bonus

