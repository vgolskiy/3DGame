# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/06 08:12:01 by mskinner          #+#    #+#              #
#    Updated: 2020/09/17 01:12:23 by mskinner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
INCS = -I./includes -I./libft -I./mlx
INCLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit -Llibft -lft
CFLAGS = -Wall -Werror -Wextra $(INCS)
LIBFT = ./libft
MLX = ./mlx

SRCS = ./srcs/bmp.c ./srcs/check_map.c ./srcs/draw.c ./srcs/exit.c\
		./srcs/get_next_line.c ./srcs/init.c ./srcs/key_handling.c\
		./srcs/main.c ./srcs/main_loop.c ./srcs/parse.c ./srcs/parse_map.c\
		./srcs/raycasting.c ./srcs/sprite.c ./srcs/sprite_utils.c\
		./srcs/texture.c ./srcs/utils.c ./srcs/draw_map.c ./srcs/transform_map.c\
		./srcs/parse2.c ./srcs/exit2.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT) bonus
	@$(MAKE) -C $(MLX)
	@$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) $(INCLIB)

clean:
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(MLX) clean
	@rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(MLX) fclean
	@rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: test bonus all clean fclean re