#include "../header/cub3d.h"

void	clean_beforeout(t_table **ptable)
{
    t_table	*table;

    if (!ptable || !*ptable)
        return ;
    table = *ptable;
    //free texture ???
    if (table->img)
        mlx_destroy_image(table->mlx, table->img);
    if (table->mlx_win)
        mlx_destroy_window(table->mlx, table->mlx_win);
    if (table->player_coor)
    {
        free_player(table->player_coor);
        table->player_coor = NULL;
    }
    if (table->map_stru)
    {
        free_map_c(table->map_stru);
        table->map_stru = NULL;
    }
    if (table->map_ele)
    {
        free_map(&table->map_ele);
        table->map_ele = NULL;
    }
    if (table->mlx)
        free(table->mlx);
    free(table);
    *ptable = NULL;
}

void clean_close(t_table **ptable)
{
    t_table *table;

    if (!ptable || !*ptable)
        return ;
    table = *ptable;
    if (table->img)
        mlx_destroy_image(table->mlx, table->img);
    //free texture ???
    if (table->mlx_win)
        mlx_destroy_window(table->mlx, table->mlx_win);

    if (table->player_coor)
    {
        free_player(table->player_coor);
        table->player_coor = NULL;
    }
    if (table->map_stru)
    {
        free_map_c(table->map_stru);
        table->map_stru = NULL;
    }
    if (table->map_ele)
    {
        free_map(&table->map_ele);
        table->map_ele = NULL;
    }
    if (table->mlx)
        free(table->mlx);

    free(table);
    *ptable = NULL;
}
