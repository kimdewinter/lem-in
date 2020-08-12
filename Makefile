# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lravier <lravier@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/28 11:20:14 by lravier       #+#    #+#                  #
#    Updated: 2020/08/11 14:55:19 by lravier       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME=lem-in
CC=gcc
EXTRA=
IFLAGS= -Wall -Wextra -Werror -O1 $(EXTRA)
RAW=	main\
		parse_antmount\
		parse_clean\
		parse_input\
		parse_error\
		parse_rooms\
		parse_tubes\
		parse_utils\
		read_input\
		room_utils\
		sanitize_input\
		route_finder\
		biter1\
		biter2\
		calc_cost\
		err_biter\
		err_route_finder\
		calc_ants_routes\
		outputter\
		roundputter\
		delete_rooms\
		un_tubes_delete\
		un_tubes_neighbours_checks\
		un_tubes_options_check\
		un_tubes_queue\
		un_tubes_remove\
		un_tubes_short_checks\
		un_tubes_utils\
		un_tubes_utils_2\
		un_setup_queue\
		un_update_queue\
		print\
		traverse_bf\
		df_routefinder\
		df_rf_executor\
		route_finder_utils\
		remove_blockage\
		compare_state_sol

OBJ_DIR=obj/
SRC_DIR=srcs/
SRCS=$(addprefix $(SRC_DIR),$(addsuffix .c,$(RAW)))
OBJS=$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
HEADER=./includes/lemin.h

# LIBRARIES #
LIB_NAME=libftprintf.a
LIB_DIR=lib/
LIB=$(LIB_DIR)$(LIB_NAME)

.PHONY: all clean fclean re

all:$(NAME)
	@echo "Compiling $(LIB_NAME)"
	@make -s -C $(LIB_DIR)
	@echo "Compiling $^ executable"
	@$(CC) $(IFLAGS) -o $(NAME) $(OBJS) -I $(HEADER) $(LIB)

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
	@$(CC) -Wall -Wextra -Werror $(EXTRA) -g -o $(NAME) $(SRCS) $(HEADER) $(LIB)
