NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar
ARFLAGS = rcs
SRC = main.c get_next_line.c get_next_line_utils.c \
	  builtin/ft_cd.c builtin/ft_echo.c builtin/ft_env.c  builtin/ft_exit.c \
	  builtin/ft_pwd.c builtin/ft_unset.c error/error_handle.c builtin/ft_export.c \
	  builtin/ft_export2.c exec/exec_utils.c exec/process.c exec/signal.c \
	  redirection/redir_exec.c redirection/redir_skip.c redirection/redir_utils.c

SRCDIR = ./srcs/

LIBFTDIR = ./libft/

INCDIR = ./includes

LIBFT = libft.a

LIBPOS = $(addprefix $(LIBFTDIR), $(LIBFT))

SRCS = $(addprefix $(SRCDIR), $(SRC))

OBJS = $(SRCS:.c=.o)
 
$(NAME): $(LIBPOS) $(OBJS)
	$(CC) $(CLFAGS) $(OBJS) libft.a -I $(INCDIR) -o $(NAME)

$(LIBPOS):
	$(MAKE) -C libft/ libft.a
	cp $(LIBPOS) libft.a

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCDIR)

all: $(NAME)
	
clean:
	rm -rf $(OBJS)
	cd $(LIBFTDIR) && make clean

fclean: clean
	rm -rf $(NAME)
	cd $(LIBFTDIR) && rm -rf $(LIBFT)
	
re: fclean all

.PHONY: all clean fclean re