# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 11:15:08 by jchartie          #+#    #+#              #
#    Updated: 2026/02/26 12:09:47 by jchartie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -O0
SRC_DIR = src/
MAIN_SOURCES = main.c
OBJ_DIR = obj/
MAIN_OBJECTS = $(addprefix $(OBJ_DIR), $(MAIN_SOURCES:.c=.o))
BONUS_OBJECTS = $(addprefix $(OBJ_DIR), $(MAIN_SOURCES:.c=.o))
NAME = so_long

# Default rule
all: $(NAME)

# Making of the libftprintf.a library without bonuses
$(NAME): $(MAIN_OBJECTS)
	cd mlx_linux && $(MAKE)
	$(CC) $(MAIN_OBJECTS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

# Compilation of the .c files into .o files (main + bonus)
# Ensure that $(OBJ_DIR) exists
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I/usr/include -Imlx_linux

# Create $(OBJ_DIR) directory if it doesn't exist
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# Phony targets declaration
.PHONY: all clean fclean re bonus

# Compilation of bonus .c files into .o files
# bonus: $(BONUS_OBJECTS) $(NAME) 
#	ar rcs $(NAME) $(BONUS_OBJECTS)

# Removal of object files
clean:
	rm -f $(MAIN_OBJECTS) $(BONUS_OBJECTS)
	if [ -d $(OBJ_DIR) ]; then rmdir $(OBJ_DIR); fi

# Removal of compiled file
fclean: clean
	cd mlx_linux && $(MAKE) clean
	rm -f $(NAME)
	

# Recompile all files
re: fclean
	$(MAKE) all

