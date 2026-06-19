NAME = ft_ls


SOURCES = main.c Helper.c parse.c manipulation.c print.c 


CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g


all : $(NAME)


$(NAME): $(SOURCES) 
	@gcc $(LINKS) $(CFLAGS) $(SOURCES) -o $(NAME)
	@echo "compiled successfully"

clean :
	@rm -f $(NAME)
fclean : clean
	
re : fclean all