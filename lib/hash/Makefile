# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lravier <lravier@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/28 20:59:39 by lravier       #+#    #+#                  #
#    Updated: 2020/04/30 17:01:05 by lravier       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = hash.a
CC = gcc
IFLAGS = -Wall -Werror -Wextra
RAWFILES = delete hash insert new_item new_table prime resize_table pow_ll \
search
CSRCS := $(addprefix srcs/,$(addsuffix .c,$(RAWFILES)))
OBJS=$(patsubst srcs/%.c,obj/%.o,$(CSRCS))
HEADER = includes/hashing.h

.PHONY: all clean fclean re

all: $(NAME)
	@ar rcs $(NAME) $(OSRCS)

obj:
	mkdir $@

obj/%.o: srcs/%.c $(HEADER) | obj
	$(CC) $(IFLAGS) -c $< -o $@

clean_obj:
	if [ -d obj ]; then rm -rf obj; fi

clean: clean_obj

fclean: clean
	@rm -f $(NAME)

re: fclean all
