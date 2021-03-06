
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
pf_doubletostr.c\
pf_utils.c\
pf_utils2.c\
ft_vprintf.c\
ft_printf.c
OBJ=$(SRC:.c=.o)

all: $(LIBFT) $(NAME)

%.o: %.c ft_printf.h
	gcc -c -Wall -Wextra -Werror -Ilibft $< -o $@ $(DEBUG)
	ar rc $(NAME) $@

$(NAME): $(OBJ)

$(LIBFT):
	$(MAKE) -C libft/ d
	cp $(LIBFT) $(NAME)

clean:
	rm -rf $(OBJ)
	$(MAKE) -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C libft/ fclean

test: all
	gcc -I. -Ilibft test.c libftprintf.a -g
	./a.out

re: fclean all
