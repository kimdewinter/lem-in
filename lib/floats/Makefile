# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lravier <lravier@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/28 20:59:39 by lravier       #+#    #+#                  #
#    Updated: 2020/10/01 15:24:54 by kde-wint      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libfloats.a
CC = gcc
IFLAGS = -Wall -Werror -Wextra
OBJ_DIR = obj/
RAWFILES = ft_frexp ft_get_string float_utilities ft_create_bigint \
ft_mult_bigint ft_div_bigint ft_round_bigint ft_create_string ft_fill_str \
ft_scale_bigint ft_create_string_e ft_get_len_zero_excep ft_zero_str \
ft_fill_string_e ft_string_exceptions ft_conv_g ft_round_e ft_shift_left \
ft_create_output ft_get_length ft_get_max_index
CSRCS = $(addsuffix .c,$(RAWFILES))
OSRCS := $(addprefix $(OBJ_DIR),$(addsuffix .o,$(RAWFILES)))
HEADER = includes/floats.h

all: $(NAME)

$(NAME): $(OSRCS)
	@ar rcs $(NAME) $(OSRCS)

$(OBJ_DIR):
	mkdir $@

obj/%.o: %.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(IFLAGS) -o $@ -c $<

clean_obj:
	if [ -d obj ]; then rm -rf obj; fi

clean: clean_obj

fclean: clean
	@rm -f $(NAME)

re: fclean all
