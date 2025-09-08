# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    print_ascii_art.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manuelma <manuelma@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/26 18:54:11 by manuelma          #+#    #+#              #
#    Updated: 2025/08/26 21:56:27 by manuelma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Dépend de: mk/colors.mk (quoté) et mk/letters.mk (NON quoté)
include mk/colors.mk
include mk/letters.mk

# Sépare en caractères et upper pour A..Z (ex: "Hello42" -> "H E L L O 4 2")
SEPARATE_CHARS = $(strip $(shell \
	printf "%s" '$(1)' | sed 's/./& /g' | tr '[:lower:]' '[:upper:]'))

# Retire " et ' (utile pour les couleurs qui sont quotées dans colors.mk)
UNQUOTE = $(subst ",,$(subst ',,$(1)))

# Choix du nom de variable glyph:
# - Lettres: A1, B2, ...
# - Chiffres: 0_1, 4_2, ...
GET_CELL = $(if $(filter $(1),0 1 2 3 4 5 6 7 8 9), \
               $($(1)_$(2)), \
               $($(1)$(2)))

# Assemble une ligne (n=1..3) sans espace devant la 1re cellule
BUILD_LINE = \
  $(call GET_CELL,$(firstword $(call SEPARATE_CHARS,$(1))),$(2)) \
  $(foreach L,$(wordlist 2,999,$(call SEPARATE_CHARS,$(1))), $(call \
  GET_CELL,$(L),$(2)))

# PRINT_LINE : n'imprime qu'une ligne du mot $(1) (ligne $(2)), sans couleurs
define PRINT_LINE
	@printf " "; \
	first_cell='$(call GET_CELL,$(firstword $(call SEPARATE_CHARS,$(1))),$(2))'; \
	first_cell="$$(printf "%s" "$$first_cell" | sed 's/^[[:space:]]\+//')"; \
	printf "%s" "$$first_cell"; \
	$(foreach L,$(wordlist 2,999,$(call SEPARATE_CHARS,$(1))), \
		printf " %s" "$(call GET_CELL,$(L),$(2))";) \
	printf "\n"
endef

# PRINT_WORD : applique la couleur $(2) une fois, imprime 3 lignes, puis Color_Off
# Usage: $(call PRINT_WORD, MOT, Color_Var)
define PRINT_WORD
	@printf "%b\n" "$(call UNQUOTE,$($(2)))"
	$(call PRINT_LINE,$(1),1)
	$(call PRINT_LINE,$(1),2)
	$(call PRINT_LINE,$(1),3)
	@printf "%b\n" "$(call UNQUOTE,$(Color_Off))"
endef

