# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpripoae <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/13 15:37:11 by mpripoae          #+#    #+#              #
#    Updated: 2018/01/13 15:37:15 by mpripoae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fillit
SRC			= *.c

OBJ			= $(SRC:%.c=%.o)
CFLAGS		= -Werror -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	gcc $(CFLAGS) $(OBJ) -L libft/ -lft -o $(NAME)

$(OBJ): $(SRC)
	gcc $(CFLAGS) -I. -c $(SRC)

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
