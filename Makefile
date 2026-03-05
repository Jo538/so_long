# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admin <admin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 11:15:08 by jchartie          #+#    #+#              #
#    Updated: 2026/03/05 17:00:43 by admin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = cc
CFLAGS = -g3 -O0
NAME = so_long
TEST_NAME = test_so_long

# Directories and Paths
SRC_DIR = src/
OBJ_DIR = obj/
GNL_DIR = libs/getnextline
TEST_DIR = test
LIBFT_DIR = libs/libft
PRINTF_DIR = libs/libftprintf

# Sources and Objects
MAIN_SOURCES = main.c	parser_1.c	clean_error.c	parser_2.c	flood_fill.c	game.c
MAIN_OBJECTS = $(addprefix $(OBJ_DIR), $(MAIN_SOURCES:.c=.o))
TEST_SOURCES = $(TEST_DIR)/main.c	$(TEST_DIR)/parser.c	$(SRC_DIR)parser_1.c	\
				$(SRC_DIR)clean_error.c	$(SRC_DIR)parser_2.c	$(SRC_DIR)flood_fill.c	\
				$(SRC_DIR)game.c
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
TEST_FLAG = TESTING

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
.PHONY: all clean fclean re test

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
	rm -rf $(TEST_NAME).dSYM
	rm -f $(TEST_NAME)
	rm -f $(NAME)

# Recompile all files
re: fclean
	$(MAKE) all

# Run tests
test: $(LIB_OBJ) $(GNL_OBJ)
	@$(CC) -D$(TEST_FLAG) $(CFLAGS) $(INCLUDES) $(MLX_FLAGS) $(TEST_SOURCES) $(GNL_OBJ) $(LIB_OBJ) -o $(TEST_NAME)
	@./$(TEST_NAME)
	

