# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lravier <lravier@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/28 20:59:39 by lravier       #+#    #+#                  #
#    Updated: 2020/06/12 17:07:44 by lravier       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libfloats.a
CC = gcc
IFLAGS = -Wall -Werror -Wextra
RAWFILES = ft_frexp ft_get_string float_utilities ft_create_bigint \
ft_mult_bigint ft_div_bigint ft_round_bigint ft_create_string ft_fill_str \
ft_scale_bigint ft_create_string_e ft_get_len_zero_excep ft_zero_str \
ft_fill_string_e ft_string_exceptions ft_conv_g ft_round_e ft_shift_left \
ft_create_output ft_get_length ft_get_max_index
CSRCS = $(addsuffix .c,$(RAWFILES))
OSRCS := $(addprefix obj/,$(addsuffix .c,$(RAWFILES)))
HEADER = includes/floats.h

all: $(NAME)

$(NAME): $(OSRCS)
	@ar rcs $(NAME) $(OSRCS)

obj:
	mkdir $@

obj/%.o: %.c $(HEADER) | obj
	$(CC) $(IFLAGS) -o $@ -c $<

clean_obj:
	if [ -d obj ]; then rm -rf obj; fi

clean: clean_obj

fclean: clean
	@rm -f $(NAME)

re: fclean all
