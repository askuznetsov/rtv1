# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/19 02:29:58 by okuznets          #+#    #+#              #
#    Updated: 2019/06/19 03:05:18 by okuznets         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC			:=	gcc
CFLAGS		:=	-O3 -Wall -Wextra
GFX			:=	-L ./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit
LIBFT		:=	libft/
NAME		:=	RTv1
SRC_PATH	:=	src/
OBJ_PATH 	:=	.obj/
LIB			:=	$(LIBFT)libft.a
SRC			:=	$(SRC_PATH)rtv.c \
				$(SRC_PATH)do_ray_tracing.c \
				$(SRC_PATH)dir_utils.c \
				$(SRC_PATH)ball_func.c \
				$(SRC_PATH)bell_func.c \
				$(SRC_PATH)barrel_func.c \
				$(SRC_PATH)flat_func.c \
				$(SRC_PATH)parse_other.c \
				$(SRC_PATH)parse_else.c \
				$(SRC_PATH)manip_shine.c \
				$(SRC_PATH)calc_shine.c \
				$(SRC_PATH)parse_input.c \
				$(SRC_PATH)inter_bell.c
			
OBJS		:= $(addprefix $(OBJ_PATH), $(SRC:%.c=%.o))

all: $(NAME)

$(NAME): $(LIB) $(OBJ_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(GFX) $(LIB) -o $(NAME)

$(LIB):
	make -C $(LIBFT)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)$(SRC_PATH)
$(OBJ_PATH)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C  $(LIBFT)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all