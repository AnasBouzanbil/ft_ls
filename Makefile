NAME = ft_ls


SOURCES = main.c Helper.c parse.c manipulation.c print.c 


CFLAGS = -Wall -Wextra -Werror -fsanitize=address 


all : $(NAME)

bonus : $(BNAME)

$(NAME): $(SOURCES) $(helpsrc)
	gcc $(LINKS) $(CFLAGS) $(SOURCES) $(helpsrc) -o $(NAME)
$(BNAME) : $(helpsrc) $(Bsrc)
	gcc $(LINKS) $(CFLAGS) $(helpsrc) $(Bsrc) -o $(BNAME)

clean :
	rm -f $(NAME) $(BNAME)
fclean : clean
	
re : fclean all