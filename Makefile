# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgelu <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/15 17:56:01 by tgelu             #+#    #+#              #
#    Updated: 2018/12/01 03:33:51 by tgelu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = fdf

SRC_PATH = ./srcs
LIB_PATH = ./lib
INC_PATH = ./includes
OBJ_PATH = ./obj

SRC_NAME = main.c \
		   fdf.c \
		   get_next_line.c \
		   utils.c \
		   mlx_utils.c \
		   parser.c \
		   keyboard.c \
		   free.c

INC_NAME = fdf.h
LIB_NAME = libftprintf.a \
		   mlx/libmlx.a
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC= $(addprefix $(SRC_PATH)/, $(SRC_NAME))
INC= $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ= $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
LIB= $(addprefix $(LIB_PATH)/, $(LIB_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_PATH)
	@make -C $(LIB_PATH)/mlx
	@$(CC) $(FLAGS) -o $@ $^ $(LIB) -L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL -framework AppKit

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INC_PATH) -I$(LIB_PATH)

clean:
	@make -C $(LIB_PATH) clean 
	@rm -rf $(OBJ) $(OBJLIB) $(OBJ_PATH)

fclean: clean
	@make -C $(LIB_PATH) fclean
	@rm -rf $(NAME)

re: fclean all
