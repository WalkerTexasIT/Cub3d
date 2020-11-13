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
FLAGS = -Werror -Wall -Wextra
LIBFT_ROOT = ./libft
FRAME = -I minilibx_opengl -framework OpenGl -framework Appkit -L minilibx_opengl -lmlx

NAME = Cub3d

SRC = utils.c		ft_free.c		parser.c		ft_strndup.c \
		main.c		bmp.c
OBJ = $(SRC:.c=.o)
	INCLUDE = cub3d.h mlx.h

all: libft_all $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -fsanitize=address $(FRAME) $(LIBFT_ROOT)/libft.a $(OBJ) -o $(NAME)

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
