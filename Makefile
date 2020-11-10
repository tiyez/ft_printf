
NAME=libftprintf.a
LIBFT_NAME=libft.a
LIBFT=$(addprefix libft/,$(LIBFT_NAME))

SRC=\
pf_draw_integer.c\
pf_draw_double.c\
pf_draw_spec.c\
pf_value.c\
pf_parse_spec.c\
pf_lltostr.c\
ft_vprintf.c\
ft_printf.c
OBJ=$(SRC:.c=.o)

all: $(LIBFT) $(NAME)

%.o: %.c ft_printf.h
	gcc -c -Wall -Wextra -Werror -Ilibft $< -o $@ -g

$(NAME): $(OBJ)
	ar rc $(NAME) $?

$(LIBFT):
	$(MAKE) -C libft/ d
	ar rc $(NAME) libft/*.o

clean:
	rm -rf $(OBJ)
	$(MAKE) -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C libft/ fclean

re: fclean all
