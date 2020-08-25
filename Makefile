# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lravier <lravier@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/28 11:20:14 by lravier       #+#    #+#                  #
#    Updated: 2020/08/25 16:34:02 by kim           ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME=lem-in
CC=gcc
EXTRA=
IFLAGS= -Wall -Wextra -Werror -O1 $(EXTRA)
RAW=	main\
		main_error\
		parse_antmount\
		parse_clean\
		parse_input\
		parse_error\
		parse_rooms\
		parse_rooms_add_room\
		parse_tubes\
		parse_utils\
		read_input\
		room_utils\
		sanitize_input\
		set_spe\
		set_sps\
		route_finder\
		find_best_option_route\
		route_finder_utils_1\
		route_finder_utils_2\
		biter1\
		biter2\
		calc_cost\
		calc_cost_add_path\
		calc_ants_routes\
		err_biter\
		outputter\
		outputter_setup\
		roundputter\
		delete_map\
		delete_rooms\
		remove_tube\
		remove_blockage_1\
		remove_blockage_2\
		compare_candidate_sol\
		set_weights\
		set_weights_utils\
		find_parallel_routes

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

$(NAME):$(OBJS)
	@echo "Compiling $(LIB_NAME)"
	@make -s -C $(LIB_DIR)
	@echo "Compiling $@ executable"
	@$(CC) $(IFLAGS) -o $(NAME) $(OBJS) -I $(HEADER) $(LIB)

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
