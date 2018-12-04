# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/05 12:24:50 by mtaquet      #+#   ##    ##    #+#        #
#    Updated: 2018/12/04 16:57:20 by mtaquet     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = fdf
LIBDIR = libft/
SRCDIR = srcs/
INCDIR = includes/
LIBFILES = libft.a
SRCFILES = input.c\
		main.c\
		event.c\
		eventmouse.c\
		draw.c\
		color.c\
		util.c\

INCFILES = fdf.h
LIB = $(addprefix $(LIBDIR),$(LIBFILES)) minilibx/libmlx.a
SRC = $(addprefix $(SRCDIR),$(SRCFILES))
INC = $(addprefix $(INCDIR),$(INCFILES))
OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra

all: $(NAME)

%.o: %.c $(INC)
	gcc -c -o $@ $< -I includes -I minilibx $(FLAG)
$(LIB):
	make -C $(LIBDIR)
	make -C minilibx

$(NAME): $(LIB) $(OBJ) $(INC)
	gcc -o $@ $(LIB) $(OBJ) -I includes -I minilibx $(FLAG) minilibx/libmlx.a -L ./libft/ -lft -framework OpenGL -framework AppKit


clean:
	rm -f $(OBJ)
	make clean -C $(LIBDIR)
	make clean -C minilibx


fclean: clean
	rm -f $(NAME)
	rm -f $(LIB)

re: fclean all
