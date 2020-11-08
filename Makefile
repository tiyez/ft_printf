
NAME=libftprintf.a
LIBFT_NAME=libft.a
LIBFT=$(addprefix libft/,$(LIBFT_NAME))

SRC=\
pf_draw_integer.c\
pf_draw_spec.c\
pf_value.c\
pf_parse_spec.c\
pf_lltostr.c\
ft_vprintf.c\
ft_printf.c
OBJ=$(SRC:.c=.o)

all: $(NAME)

%.o: %.c ft_printf.h
	gcc -c -Wall -Wextra -Werror $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	ar rc $(NAME) $^

$(LIBFT):
	$(MAKE) -D libft/ d

clean:
	rm -rf $(OBJ)
	rm -rf add
	$(MAKE) -D libft/ clean

fclean: clean
	rm -rf 
	$(MAKE) -D libft/ fclean

re: fclean all
