# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chatou <chatou@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 20:05:24 by chatou            #+#    #+#              #
#    Updated: 2025/04/21 20:59:12 by chatou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = part_converter

# Fichiers sources
SRCS = part_converter.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Options du compilateur
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

# Règle par défaut
all: $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Compilation des fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers générés
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f partition.c

# Recompilation complète
re: fclean all

# Test rapide
run: all
	./$(NAME)