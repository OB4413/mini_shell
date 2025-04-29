programe = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

src = minishell.c Tokenization.c Variable_Expansion.c parsing_tokns.c
obj = $(src:.c=.o)
libft = libft/libft.a

all: $(programe) clean

$(programe): $(obj) $(libft)
	$(CC) $(CFLAGS) $(obj) $(libft) -o $(programe) -lreadline -lhistory

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(libft):
	make -C libft

clean:
	rm -f $(obj)
	make -C libft clean

fclean: clean
	rm -f $(programe)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(obj)
