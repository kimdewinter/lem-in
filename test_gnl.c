// #include "libftprintf/libft/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
# include <unistd.h>
# include <string.h>
int main()
{
	char c;
	int	last_read;

	// last_read = 1;
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		// last_read = read(1, line, 1);
		// exit (0);
		printf("%c\n", c);
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