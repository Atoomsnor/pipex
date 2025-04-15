NAME		= pipex
NAME_B		= pipex_bonus

LIBFT		= libft/libft.a

SRCDIR		= source
SRCLIT		= pipex.c pathfinding.c
SRCS		= $(addprefix $(SRCDIR)/, $(SRCLIT))
OBJ			= $(SRCS:.c=.o)

SRCLIT_B	= pipex_bonus.c pathfinding_bonus.c
SRCS_B		= $(addprefix $(SRCDIR)/, $(SRCLIT_B))
OBJ_B		= $(SRCS_B:.c=.o)

CC			= cc
INCLUDE		= -I ./include -I libft/
CFLAGS		= -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

bonus: $(NAME_B)

$(NAME_B): $(LIBFT) $(OBJ_B)
	$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT) -o $(NAME_B)

$(LIBFT): 
	$(MAKE) -C libft

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -f $(OBJ) $(OBJ_B)
	$(MAKE) -C libft clean

fclean: clean
	@rm -f $(NAME) $(NAME_B)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re