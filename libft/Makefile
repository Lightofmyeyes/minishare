# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: lcosta-a <lcosta-a@student.42.fr>          +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2025/12/06 04:05:00 by lcosta-a        #+#    #+#               #
#   Updated: 2025/12/13 21:30:00 by lcosta-a       ###   ########.fr         #
#                                                                            #
# ************************************************************************** #

# ==============================================
# ============= VARIÁVEIS GLOBAIS ==============
# ==============================================

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.

# Lista completa de arquivos fonte da libft
SRCS = \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlen.c \
	ft_strlcpy.c \
	ft_strcmp.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_strncpy.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_printf.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_putunbr.c \
	ft_putnbr.c \
	ft_puthex.c \
	ft_putptr.c \
	ft_printf.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_putunbr.c \
	ft_putnbr.c \
	ft_puthex.c \
	ft_putptr.c \
	ft_lstnew_bonus.c \
        ft_lstadd_front_bonus.c \
        ft_lstsize_bonus.c \
        ft_lstlast_bonus.c \
        ft_lstadd_back_bonus.c \
        ft_lstdelone_bonus.c \
        ft_lstclear_bonus.c \
        ft_lstiter_bonus.c \
        ft_lstmap_bonus.c

# Objetos gerados a partir dos fontes
OBJS = $(SRCS:.c=.o)

# ==============================================
# ================ REGRAS PRINCIPAIS ===========
# ==============================================

all: $(NAME)

# Regra principal que compila a libft
$(NAME): $(OBJS)
	ar rcs $@ $^
	@echo "✅ $(NAME) compilado com sucesso!"

# Regra para compilar os objetos da libft
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ==============================================
# ============= REGRAS DE LIMPEZA ==============
# ==============================================

clean:
	rm -f $(OBJS)
	@echo "🧹 Objetos removidos!"

fclean: clean
	rm -f $(NAME)
	@echo "🗑️ $(NAME) removido!"

re: fclean all
	@echo "🔄 Recompilação completa!"

.PHONY: all clean fclean re
