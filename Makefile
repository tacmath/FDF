# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/05 12:24:50 by mtaquet      #+#   ##    ##    #+#        #
#    Updated: 2018/12/05 14:23:22 by mtaquet     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = fdf
LIBDIR = libft/
MLXDIR = minilibx/
SRCDIR = srcs/
INCDIR = includes/
LIBFILES = libft.a
MLXFILES = libmlx.a
SRCFILES = input.c\
		   init.c\
		   main.c\
		   event.c\
		   eventmouse.c\
		   draw.c\
		   color.c\
		   util.c\

INCFILES = fdf.h
LIB = $(addprefix $(LIBDIR),$(LIBFILES))
MLX = $(addprefix $(MLXDIR),$(MLXFILES))
SRC = $(addprefix $(SRCDIR),$(SRCFILES))
INC = $(addprefix $(INCDIR),$(INCFILES)) minilibx/mlx.h
OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra -I includes -I minilibx

all: $(NAME)

%.o: %.c $(INC)
	gcc -c -o $@ $< $(FLAG)

$(LIB):
	make -C $(LIBDIR)

$(MLX):
	make -C $(MLXDIR)

$(NAME): $(LIB) $(MLX) $(OBJ) $(INC)
	gcc -o $@ $(LIB) $(MLX) $(OBJ) $(FLAG) -framework OpenGL -framework AppKit


clean:
	rm -f $(OBJ)
	make clean -C $(LIBDIR)
	make clean -C minilibx


fclean: clean
	rm -f $(NAME)
	rm -f $(LIB)

re: fclean all
