#include "header/cub3d.h"

void sys()
{
    system("leaks cub3d");
}


int main(int ac, char *arg[])
{
    atexit(sys);
    if (ac != 2)
        return (ft_putstr_fd("Error\n\tnot enough arguments\n", 2), -1);
    if (!check_map_extention(arg[1]))
        return -1;
}
