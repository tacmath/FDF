# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/05 12:24:50 by mtaquet      #+#   ##    ##    #+#        #
#    Updated: 2018/11/16 11:24:27 by mtaquet     ###    #+. /#+    ###.fr      #
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

INCFILES = fdf.h
LIB = $(addprefix $(LIBDIR),$(LIBFILES))
SRC = $(addprefix $(SRCDIR),$(SRCFILES))
INC = $(addprefix $(INCDIR),$(INCFILES))
OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra

all: $(NAME)

%.o: %.c $(INC)
	gcc -c -o $@ $< -I includes $(FLAG)
$(LIB):
	make -C $(LIBDIR)

$(NAME): $(LIB) $(OBJ) $(INC)
	gcc -o $@ $(LIB) $(OBJ) -I includes $(FLAG) -L ./libft/ -lft


clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBDIR)


fclean: clean
	rm -f $(NAME)
	rm -f $(LIB)

re: fclean all
