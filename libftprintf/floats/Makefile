NAME = libfloats.a
CC = gcc
IFLAGS = -Wall -Werror -Wextra -g
RAWFILES = ft_frexp ft_get_string float_utilities ft_create_bigint \
ft_mult_bigint ft_div_bigint ft_round_bigint ft_create_string ft_fill_str \
ft_scale_bigint ft_create_string_e ft_get_len_zero_excep ft_zero_str \
ft_fill_string_e ft_string_exceptions ft_conv_g ft_round_e ft_shift_left \
ft_create_output ft_get_length ft_get_max_index
CSRCS = $(addsuffix .c,$(RAWFILES))
OSRCS := $(addsuffix .o,$(RAWFILES))
HEADER = includes/floats.h

all: $(NAME)

$(NAME): $(OSRCS)
	@libtool -static -o $(NAME) $(OSRCS)

%.o: %.c $(HEADER)
	$(CC) $(IFLAGS) -o $@ -c $<

clean:
	@rm -f *.o *~
	rm -f includes/floats.h.gch

fclean: clean
	@rm -f $(NAME)

re: fclean all