# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roversch <roversch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 13:55:47 by roversch          #+#    #+#              #
#    Updated: 2025/02/17 14:06:23 by roversch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_gnl.a
SRCDIR = source
SRCLIT = get_next_line.c get_next_line_utils.c
SRCS	= $(addprefix $(SRCDIR)/,$(SRCLIT))
OBJ		= $(SRCS:.c=.o)
CC = cc
INCLUDE = -I ./include
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

%.o: %.c
	@$(CC) -c $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re