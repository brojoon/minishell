NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar
ARFLAGS = rcs
SRC = main.c parsing/get_next_line/get_next_line.c parsing/ft_error.c\
	  parsing/get_next_line/get_next_line_utils.c parsing/ft_cursor.c \
	  parsing/ft_instlst.c parsing/env_lst/ft_env_lst.c \
	  parsing/inst_split/ft_inst_split_01.c parsing/ft_cursor_cases.c\
	  parsing/inst_split/ft_inst_split_02.c parsing/inst_split/ft_inst_split_03.c \
	  parsing/inst_split/ft_inst_split_utils.c parsing/libft/libft_01.c \
	  parsing/quotes/ft_quotes_01.c parsing/quotes/ft_quotes_02.c \
	  parsing/quotes/ft_quotes_03.c parsing/quotes/ft_quotes_utils.c \
	  parsing/string_lst/ft_string_lst.c parsing/string_lst/ft_string_utils.c \
	  exec/builtin/ft_cd.c exec/builtin/ft_echo.c exec/builtin/ft_env.c \
	  exec/builtin/ft_exit.c exec/builtin/ft_pwd.c exec/builtin/ft_unset.c \
	  exec/builtin/ft_export.c exec/builtin/ft_export2.c exec/builtin/ft_export3.c\
	  exec/error/error_handle.c exec/process/exec_utils.c exec/process/exec_proc.c \
	  exec/process/signal.c exec/redirection/redir_exec.c exec/redirection/redir_skip.c \
	  exec/redirection/redir_utils.c

SRCDIR = ./srcs/

LIBFTDIR = ./srcs/exec/libft/

INCDIR = ./includes

LIBFT = libft.a

LIBPOS = $(addprefix $(LIBFTDIR), $(LIBFT))

SRCS = $(addprefix $(SRCDIR), $(SRC))

OBJS = $(SRCS:.c=.o)
 
$(NAME): $(LIBPOS) $(OBJS)
	$(CC) $(CLFAGS) $(OBJS) libft.a -I $(INCDIR) -o $(NAME) -lncurses #-fsanitize=address

$(LIBPOS):
	$(MAKE) -C ./srcs/exec/libft/ libft.a
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
