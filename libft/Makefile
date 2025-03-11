# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roversch <roversch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 15:49:19 by roversch          #+#    #+#              #
#    Updated: 2025/02/24 15:01:04 by roversch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_atoi.c ft_atol.c ft_bzero.c ft_putstr.c ft_split.c ft_strmapi.c \
ft_striteri.c ft_calloc.c ft_itoa.c ft_putstr_fd.c ft_putnbr_fd.c \
ft_putnbr.c ft_putendl_fd.c ft_putchar_fd.c ft_strjoin.c ft_strtrim.c \
ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c \
ft_toupper.c

OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I ./include -I printf/include -I get_next_line/include

# Directories
PRINTF_DIR = printf/source
GNL_DIR = get_next_line/source

# Source files for printf & get_next_line
PRINTF_SRC = ft_printf.c printf_base10.c printf_base16.c printf_chars.c
GNL_SRC = get_next_line.c get_next_line_utils.c

# Object files for printf & get_next_line (fixed)
PRINTF_OBJ = $(addprefix $(PRINTF_DIR)/, $(PRINTF_SRC:.c=.o))
GNL_OBJ = $(addprefix $(GNL_DIR)/, $(GNL_SRC:.c=.o))

# All object files
ALL_OBJ = $(OBJ) $(PRINTF_OBJ) $(GNL_OBJ)

all: $(NAME)

$(NAME): $(ALL_OBJ)
	@ar rc $(NAME) $(ALL_OBJ)

# Compile libft objects
%.o: %.c
	@$(CC) -c $(CFLAGS) -o $@ $< $(INCLUDE)

# Compile printf objects correctly
$(PRINTF_DIR)/%.o: $(PRINTF_DIR)/%.c
	@$(CC) -c $(CFLAGS) -o $@ $< $(INCLUDE)

# Compile get_next_line objects correctly
$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	@$(CC) -c $(CFLAGS) -o $@ $< $(INCLUDE)

clean:
	@rm -f $(OBJ) $(PRINTF_OBJ) $(GNL_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re