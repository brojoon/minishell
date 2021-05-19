\=ㅎㄱ9 # **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/30 02:56:08 by hyungjki          #+#    #+#              #
#    Updated: 2021/01/21 08:12:06 by hyungjki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_j.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar
ARFLAGS = rcs
SRCS = ft_memset_j.c ft_bzero_j.c ft_memcpy_j.c ft_memccpy_j.c \
		ft_memmove_j.c ft_memchr_j.c ft_memcmp_j.c ft_strlen_j.c \
		ft_strlcpy_j.c ft_strlcat_j.c ft_strchr_j.c ft_strrchr_j.c \
		ft_strnstr_j.c ft_strncmp_j.c ft_atoi_j.c ft_isalpha_j.c \
		ft_isdigit_j.c ft_isalnum_j.c ft_isascii_j.c ft_isprint_j.c \
		ft_toupper_j.c ft_tolower_j.c ft_calloc_j.c ft_strdup_j.c ft_strcmp_j.c \
		ft_substr_j.c ft_strjoin_j.c ft_strtrim_j.c ft_split_j.c \
		ft_itoa_j.c ft_strmapi_j.c ft_putchar_fd_j.c ft_putstr_fd_j.c \
		ft_putendl_fd_j.c ft_putnbr_fd_j.c
SRCS_BONUS = ft_lstnew_j.c ft_lstadd_front_j.c ft_lstsize_j.c ft_lstlast_j.c \
		ft_lstadd_back_j.c ft_lstdelone_j.c ft_lstclear_j.c ft_lstiter_j.c \
		ft_lstmap_j.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
ifdef WITH_BONUS
	OBJ_FILES = $(OBJS_BONUS)
else
	OBJ_FILES = $(OBJS)
endif
all: $(NAME)
$(NAME): $(OBJ_FILES)
ifdef WITH_BONUS
	$(AR) $(ARFLAGS) $(NAME) $(OBJS_BONUS)
else
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
endif
$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $<
bonus:
	make WITH_BONUS=1 all
$(OBJS_BONUS): %.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(OBJS) $(OBJS_BONUS)
fclean: clean
	rm -rf $(NAME)
re: fclean all

.PHONY: all bonus clean fclean re