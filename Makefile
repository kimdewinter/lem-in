# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lravier <lravier@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/28 11:20:14 by lravier       #+#    #+#                  #
#    Updated: 2020/05/06 13:54:26 by lravier       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME=lem-in
CC=gcc
IFLAGS= #-Wall -Wextra -Werror
RAW=main read_input
SRCS=$(addprefix srcs/,$(addsuffix .c,$(RAW)))
OBJS=$(patsubst srcs/%.c,obj/%.o,$(SRCS))
HEADER=./includes/lem-in.h
LIB=lib/libftprintf.a

.PHONY: all clean fclean re

all:$(NAME)
	make -C lib
	$(CC) $(IFLAGS) -o $(NAME) $(OBJS) $(HEADER) $(LIB)

$(NAME):$(OBJS)

obj:
	mkdir $@

obj/%.o: srcs/%.c $(HEADER) | obj
	$(CC) $(IFLAGS) -o $@ -c $<

clean_obj:
	if [ -d obj ]; then rm -rf obj; fi

clean: clean_obj
	make clean -C lib
fclean: clean
	make fclean -C lib
	rm -f $(NAME)

re: fclean all
