# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admin <admin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 11:15:08 by jchartie          #+#    #+#              #
#    Updated: 2026/02/26 18:58:53 by admin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(shell uname), Darwin)
	INCLUDES = -Imlx_macos
	MLX_DIR = mlx_macos
	MLX_FLAGS = -Lmlx_macos -lmlx -framework OpenGL -framework AppKit
else
	INCLUDES = -I/usr/include -Imlx_linux
    MLX_DIR = mlx_linux
	MLX_FLAGS = -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
endif

CC = cc
CFLAGS = -g3 -O0
SRC_DIR = src/
MAIN_SOURCES = main.c
OBJ_DIR = obj/
MAIN_OBJECTS = $(addprefix $(OBJ_DIR), $(MAIN_SOURCES:.c=.o))
BONUS_OBJECTS = $(addprefix $(OBJ_DIR), $(MAIN_SOURCES:.c=.o))
NAME = so_long

# Default rule
all: $(NAME)

# Make the mlx archive (no linking yet)
# Make the so_long executable, linking all object files together
# objects: project's in src/, mlx archive, frameworks/dependencies to interact with display server
$(NAME): $(MAIN_OBJECTS)
		cd $(MLX_DIR) && $(MAKE)
		$(CC) $(MAIN_OBJECTS) $(MLX_FLAGS) -o $(NAME)

# Compilation of the .c files into .o files (main + bonus)
# Ensure that $(OBJ_DIR) exists
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES)

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
	cd $(MLX_DIR) && $(MAKE) clean
	rm -f $(NAME)

# Recompile all files
re: fclean
	$(MAKE) all

