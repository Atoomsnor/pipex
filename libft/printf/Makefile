# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roversch <roversch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 15:21:20 by roversch          #+#    #+#              #
#    Updated: 2025/02/17 14:05:14 by roversch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_printf.a
SRCDIR = source
SRCLIT = ft_printf.c printf_base10.c printf_base16.c printf_chars.c
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