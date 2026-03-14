# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admin <admin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 11:15:08 by jchartie          #+#    #+#              #
#    Updated: 2026/03/14 13:48:27 by admin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long

# Directories and Paths
SRC_DIR = src/
OBJ_DIR = obj/
GNL_DIR = libs/getnextline
TEST_DIR = test
LIBFT_DIR = libs/libft
PRINTF_DIR = libs/libftprintf

# Sources and Objects
MAIN_SOURCES = main.c	parser_1.c	parser_2.c	clean_error.c	events.c	\
				flood_fill_1.c	flood_fill_2.c	hooks.c	rendering_1.c	\
				rendering_2.c
MAIN_OBJECTS = $(addprefix $(OBJ_DIR), $(MAIN_SOURCES:.c=.o))
GNL_SOURCES = get_next_line_utils.c	get_next_line.c
GNL_OBJ = $(addprefix $(GNL_DIR)/, $(GNL_SOURCES:.c=.o))
LIB_OBJ = $(LIBFT_DIR)/libft.a $(PRINTF_DIR)/libftprintf.a	$(MLX_DIR)/libmlx.a

# Libraries and Flags
ifeq ($(shell uname), Darwin)
	MLX_DIR = libs/mlx_macos
	INCLUDES = -I$(MLX_DIR)
	MLX_FLAGS = -framework OpenGL -framework AppKit
else
    MLX_DIR = libs/mlx_linux
	INCLUDES = -I$(MLX_DIR) -I/usr/include
	MLX_FLAGS = -L/usr/lib -lXext -lX11 -lm -lz
endif
INCLUDES += -Iincludes -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(GNL_DIR)

# Default rule
all: $(NAME)

# Make the so_long executable
$(NAME): $(MAIN_OBJECTS) $(GNL_OBJ) $(LIB_OBJ)
		$(CC) $(MAIN_OBJECTS) $(GNL_OBJ) $(LIB_OBJ) $(MLX_FLAGS) -o $(NAME)

# Make each library $(@D) expands to the .a directory
%.a:
	$(MAKE) -C $(@D)

# Make the project's object files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES)

# Make GNL object files
$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

# Phony targets declaration
.PHONY: all clean fclean re

# Clean project's object files
clean:
	rm -f $(MAIN_OBJECTS)
	@if [ -d $(OBJ_DIR) ]; then rmdir $(OBJ_DIR); fi

# Clean project's so_long executable and clean libraries
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(GNL_OBJ)
	rm -f $(NAME)

# Recompile all files
re: fclean
	$(MAKE) all
