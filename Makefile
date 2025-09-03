# ----------------------------- #
#         변수 설정             #
# ----------------------------- #

# 실행 파일 이름
NAME = cub3D

# 컴파일러 및 플래그
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# 소스 파일 및 오브젝트 파일 경로
SRCS_DIR = ./codes/
OBJS_DIR = ./objs/

# MiniLibX 라이브러리 경로 및 플래그
MLX_DIR = ./minilibx/
# MiniLibX 라이브러리 파일 경로
MLX_LIB = $(MLX_DIR)libmlx.a
# macOS 용 MiniLibX 플래그
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm
# Linux 용 MiniLibX 플래그 (macOS 사용 시 주석 처리)
# MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# 헤더 파일 경로 포함
INCLUDES = -I./includes -I$(MLX_DIR)

# 소스 파일 목록 (여기에 .c 파일을 추가하세요)
SRCS = main.c \
	   move.c \

# 오브젝트 파일 목록 (자동 생성)
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

# 기본 규칙: 'make' 실행 시 최종 프로그램을 빌드
all: $(NAME)

# 최종 실행 파일 생성 규칙
$(NAME): $(MLX_LIB) $(OBJS)
	@echo "Linking object files to create $(NAME)..."
	@$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(NAME) has been created successfully! ✅"

# MiniLibX 라이브러리 컴파일 규칙 추가
$(MLX_LIB):
	@echo "Compiling MiniLibX library..."
	@$(MAKE) -C $(MLX_DIR)

# 오브젝트 파일 생성 규칙
# .c 파일을 .o 파일로 컴파일하고 objs/ 폴더에 저장
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 정리 규칙
clean:
	@echo "Removing object files..."
	@rm -rf $(OBJS_DIR)
	@echo "Done."

# 전체 정리 규칙
fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)
	@echo "Done."

# 재컴파일 규칙
re: fclean all

# 가짜 규칙 (실제 파일과 이름이 겹치는 것을 방지)
.PHONY: all clean fclean re