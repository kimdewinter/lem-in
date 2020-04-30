
#include "../includes/lem-in.h"

/*ssize_t	*setup_room(t_room *dest)
{
	
	return (EXIT_SUCCESS);
}

ssize_t	setup_map(t_map *dest)
{
	t_map	map;

	map.antmount = 0;
	if (setup_room(&map.start) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}*/

int main()
{
	t_map	map;
	t_input_reader	input;

	// map.antmount = 0;
	// map.start = NULL;
	//map.routes = iets;
	if (read_input(&map, &input) == EXIT_FAILURE
		|| parse_input(&input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
}
