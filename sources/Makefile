# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by jpirsch           #+#    #+#              #
#    Updated: 2015/03/11 21:40:30 by jpirsch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	../fdf
SRC		= 	main.c \
			get_next_line.c \
	 		parse.c \
			mlx_env.c \
			hook.c \
		 	drawline.c \
			coord.c
OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(FLAGS) $(OBJ) -L ../libft/ -lft -L ../minilibx/ \
		-lmlx -framework OpenGL -framework AppKit

$(OBJ):
	gcc -c $(FLAGS) $(SRC) -I ../includes

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
