# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: lcosta-a <lcosta-a@student.42.fr>          +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2025/12/06 04:05:00 by lcosta-a        #+#    #+#             #
#   Updated: 2025/12/06 04:30:00 by lcosta-a       ###   ########.fr         #
#                                                                            #
# ************************************************************************** #

# ==============================================
# ============= VARIÁVEIS GLOBAIS ==============
# ==============================================

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.

# Lista de arquivos fonte do minishell
SRC = tokenizer.c tokenizer_utils.c token_creator.c token_utils.c main.c
OBJ = $(SRC:.c=.o)

# Configuração da libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Flags do readline
READLINE_FLAGS = -lreadline

# ==============================================
# ================ REGRAS PRINCIPAIS ===========
# ==============================================

all: $(NAME)

# Regra principal que compila o minishell
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_DIR)/libft.a $(READLINE_FLAGS)

# Regra para compilar os objetos do minishell
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ==============================================
# ============= INTEGRAÇÃO COM LIBFT ===========
# ==============================================

# Regra para compilar a libft (se não existir)
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Garante que os objetos do minishell dependem da libft
$(OBJ): | $(LIBFT)

# ==============================================
# ============= REGRAS DE LIMPEZA ==============
# ==============================================

clean:
	rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
