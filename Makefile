NAME = ft_printf.a
CC = cc
FLAG = -Wall -Wextra -Werror
SRC = ft_printf.c
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAG) -c $(SRC)
	ar -rc $(NAME) $(OBJ)

clean:
		rm -rf $(OBJ)
fclean: clean
		rm -rf $(NAME)
re: fclean all

.PHONY: all clean fclean re
