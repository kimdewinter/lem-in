#include "libftprintf/libft/get_next_line.h"
#include <stdio.h>

int main()
{
	char line[100];

	while (read(1, line, 1))
	{
		printf("%s\n", line);
	}
	// while (get_next_line(1, &line))
	// {
	// 	if (line)
	// 	{
	// 		printf("%s\n", line);
	// 		free (line);
	// 		line = NULL;
	// 	}
	// }
}