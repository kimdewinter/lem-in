# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lravier <lravier@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/28 11:20:14 by lravier       #+#    #+#                  #
#    Updated: 2020/05/22 16:10:00 by lravier       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME=lem-in
CC=gcc
EXTRA=
IFLAGS= -Wall -Wextra -Werror $(EXTRA)
RAW=					main \
						parse_antmount \
						parse_input \
						parse_rooms \
						parse_tubes \
						parse_utils	\
						read_input \
						room_utils	\
						sanitize_input \
						debug	\
						route_utils	\
						route_finder	\
						biter	\
						combinatron
OBJ_DIR=obj/
SRC_DIR=srcs/
SRCS=$(addprefix $(SRC_DIR),$(addsuffix .c,$(RAW)))
OBJS=$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
HEADER=./includes/lem-in.h

# LIBRARIES #
LIB_NAME=libftprintf.a
LIB_DIR=lib/
LIB=$(LIB_DIR)$(LIB_NAME)

.PHONY: all clean fclean re

all:$(NAME)
	@echo "Compiling $(LIB_NAME)"
	@make -s -C $(LIB_DIR)
	@echo "Compiling $^ executable"
	@$(CC) $(IFLAGS) -o $(NAME) $(OBJS) $(HEADER) $(LIB)

$(NAME):$(OBJS)

$(OBJ_DIR):
	@mkdir $@

$(OBJ_DIR)%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@$(CC) $(IFLAGS) -o $@ -c $<

clean_obj:
	@if [ -d obj ]; then rm -rf obj; fi

clean: clean_obj
	@echo "Cleaning repository"
	@echo "Cleaning repository $(LIB_DIR)"
	@make clean -s -C lib

fclean: clean
	@echo "Removing $(NAME)"
	@echo "Removing $(LIB)"
	@make fclean -s -C lib
	@rm -f $(NAME)

re: fclean all

debug: all
	@$(CC) $(IFLAGS) -g -o $(NAME) $(SRCS) $(HEADER) $(LIB)
