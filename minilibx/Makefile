#
# Makefile for MiniLibX
#

CC = cc
CFLAGS = -O2 -DSTRINGPUTX11

# MiniLibX를 구성하는 모든 소스 파일 목록입니다.
SRC =	mlx_shaders.c \
	mlx_xpm.c \
	mlx_png.c \
	mlx_opengl.m \
	mlx_new_window.m \
	mlx_init_loop.m \
	mlx_new_image.m \
	mlx_mouse.m \
	mlx_int_str_to_wordtab.c

# 소스 파일(.c, .m)로부터 목적 파일(.o) 이름을 자동으로 생성합니다.
OBJ = $(SRC:.c=.o)
OBJS = $(OBJ:.m=.o)

NAME = libmlx.a

# 최종 목표: libmlx.a 라이브러리 파일을 생성합니다.
all: $(NAME)

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re