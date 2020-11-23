# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bminner <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/28 14:54:39 by bminner           #+#    #+#              #
#    Updated: 2019/10/28 15:23:03 by bminner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
HEADER_PATH = ./inc
FLAGS = -Werror -Wall -Wextra -fsanitize=address
LIBFT_ROOT = ./libft
FRAME = -I minilibx_opengl -framework OpenGl -framework Appkit -L minilibx_opengl -lmlx

NAME = Cub3d

SRC = srcs/utils.c		srcs/ft_free.c		srcs/parser.c		srcs/ft_strndup.c \
		srcs/main.c		srcs/bmp.c			srcs/tex.c			srcs/dda.c \
		srcs/ddraw.c	srcs/key.c			srcs/parsemap.c		srcs/rgb.c \
		srcs/sprite.c	srcs/value.c		srcs/spritesecond.c
OBJ = $(SRC:.c=.o)
	INCLUDE = cub3d.h mlx.h

all: libft_all $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(FRAME) $(LIBFT_ROOT)/libft.a $(OBJ) -o $(NAME) -I $(HEADER_PATH)

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

libft_all:
		$(MAKE) -C $(LIBFT_ROOT) all
libft_clean:
		$(MAKE) -C $(LIBFT_ROOT) clean
libft_fclean:
		$(MAKE) -C $(LIBFT_ROOT) fclean

clean: libft_clean
	rm -f $(OBJ)

fclean: libft_fclean clean
	rm -f $(NAME)

re: fclean all
