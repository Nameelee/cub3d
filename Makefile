# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 16:41:17 by manuelma          #+#    #+#              #
#    Updated: 2025/09/08 23:35:19 by manuelma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========================= Nom de l'exécutable final =========================
NAME				= cub3d

# ================================ Compilation ================================
CC					= cc
CFLAGS				= -Wall -Wextra -Werror -g

# ================================= Dossiers ==================================
OBJ_DIR				= objs
SRCS_DIR			= src/
M_PARSE_DIR			= $(SRCS_DIR)map_parsing/

# ---------------- main ----------------
SRCS_MAIN			= main.c

# ------------- map parse --------------
SRCS_M_PARSE		= read_file.c strs_utils.c

SRCS				= $(addprefix $(SRCS_DIR), $(SRCS_MAIN)) \
					  $(addprefix $(M_PARSE_DIR), $(SRCS_M_PARSE))

# Transformation en objets (ex: src/foo.c -> objs/src/foo.o)
OBJS				= $(SRCS:%.c=$(OBJ_DIR)/%.o)

# ================================ Includes ===================================
PROJ_INC			= -I$(SRCS_DIR) -I$(M_PARSE_DIR)

# Libft
LIBFT_PATH			= libft
LIBFT				= $(LIBFT_PATH)/libft.a
LIBFT_INC			= -I$(LIBFT_PATH)

# get_next_line
GNL_PATH			= get_next_line
GNL					= $(GNL_PATH)/get_next_line.a
GNL_INC				= -I$(GNL_PATH)

# ============================================================================ #
#                                    Règles                                    #
# ============================================================================ #

# Règle principale
all: $(LIBFT) $(GNL) $(NAME)

# Création de l'exécutable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GNL) -o $(NAME)
	@printf "Cub3d compiled successfully!\n"

# Objets dans objs/
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(PROJ_INC) $(LIBFT_INC) $(GNL_INC) -c $< -o $@

# ============================== Sous-projets =================================

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory

$(GNL):
	@$(MAKE) -C $(GNL_PATH) --no-print-directory

# ================================= Nettoyage =================================

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory
	@$(MAKE) -C $(GNL_PATH) clean --no-print-directory
	@printf "Removed all object files from cub3d and subprojects.\n"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory || \
	 $(MAKE) -C $(LIBFT_PATH) clean_exec --no-print-directory
	@$(MAKE) -C $(GNL_PATH) fclean --no-print-directory || true
	@printf "Removed executable and libraries.\n"

re: fclean all

.PHONY: all clean fclean re

