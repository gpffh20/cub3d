#include "../include/cub3D.h"

int main(int ac, char **av)
{
	if (ac != 2)
		error_exit("Error: Wrong Number Of Arguments.\n");
	invalid_file(av[1]);
	// get_map();
	// printf("%s\n", "hello world!");
	return (0);
}
