# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 11:15:08 by jchartie          #+#    #+#              #
#    Updated: 2025/12/04 12:45:16 by jchartie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
ROOT_DIR = ~/libftprintf/
CFLAGS = -Wall -Wextra -Werror
MAIN_SOURCES = ft_printf.c	flag_c.c	flag_s.c	flag_p.c	flag_d_i.c	flag_u.c \
	ft_strncmp.c	flag_x.c
BONUS_SOURCES = 
# LIBFT_DIR = libft/
# LIBFT_NAME = libft.a
MAIN_OBJECTS = $(MAIN_SOURCES:.c=.o)
BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)
NAME = libftprintf.a
# EXEC_FILE = a.out

# Default rule
all: $(NAME)

# Making of the libftprintf.a library without bonuses
$(NAME): $(MAIN_OBJECTS)
	ar rcs $(NAME) $(MAIN_OBJECTS)
#	@cd $(LIBFT_DIR) && $(MAKE)
#	@cd $(ROOT_DIR)
#	mv $(LIBFT_DIR)$(LIBFT_NAME) $(LIBFT_NAME)

# Compilation of the .c files into .o files (main + bonus)
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

# Phony targets declaration
.PHONY: all clean fclean re bonus

# Compilation of bonus .c files into .o files
# bonus: $(BONUS_OBJECTS) $(NAME) 
#	ar rcs $(NAME) $(BONUS_OBJECTS)

# Removal of object files
clean:
#	@cd $(LIBFT_DIR) && $(MAKE) clean
#	@cd $(ROOT_DIR)
	rm -f $(MAIN_OBJECTS) $(BONUS_OBJECTS)
#	rm -f $(EXEC_FILE)

# Removal of compiled file
fclean: clean
#	@cd $(LIBFT_DIR) && $(MAKE) fclean
#	@cd $(ROOT_DIR)
	rm -f $(NAME)

# Recompile all files
re: fclean all

