#include "../header/cub3d.h"

int count_height(char **line)
{
    int i = 0;
    while (line[i])
    {
        i++;
    }
    return i;
}

int keycode(int key, void *param)
{
    t_table *table = (t_table *)param;
    if (!table)
        return 0;

    if (key == 53 || key == 2944)
        exit(1);

    if (key == 1)
        table->player_coor->forword_backword = -1;
    else if (key == 13)
        table->player_coor->forword_backword = 1;
    else if (key == 2)
        table->player_coor->leftvu_rightvu = 1;
    else if (key == 0)
        table->player_coor->leftvu_rightvu = -1;
    else if (key == 123)
        table->player_coor->rotate = -1;
    else if (key == 124)
        table->player_coor->rotate = 1;
    player_coordonneup(&table);
    return 0;
}

int relase_keycode(int keycode, t_table *data)
{
    player *player_data = data->player_coor;
    if (keycode == 13 || keycode == 1)
        player_data->forword_backword = 0;
    else if (keycode == 0 || keycode == 2)
        player_data->leftvu_rightvu = 0;
    else if (keycode == 123 || keycode == 124)
        player_data->rotate = 0;
    return 0;
}

int close_window(void *param)
{
    (void)param;
    // t_table *table = (t_table *)param;
    exit(0);
    return 0;
}

void cast_all_rays(t_table *table)
{
    double ray_angle = table->player_coor->angle - (FOV_ANGLE / 2);
    for (int i = 0; i < NUM_RAYS; i++)
    {
        cast_rays(table, ray_angle, i);
        ray_angle += FOV_ANGLE / NUM_RAYS;
    }
}

int mainloop(void *param)
{
    t_table *table = (t_table *)param;
    put_texture(table);
    ft_put_player(&table);
    cast_all_rays(table);
    return 0;
}

int rander_map(map_valid **map_element, map_cub **map_structure, player **player_cor)
{
    t_table *table;
    t_data *data2;

    data2 = malloc(sizeof(t_data));
    table = malloc(sizeof(t_table));
    table->mlx = mlx_init();
    table->map_stru = *map_structure;
    table->map_ele = *map_element;
    table->player_coor = *player_cor;
    table->data = data2;

    table->width = ft_strlen(table->map_stru->dmaps[0]);
    table->height = count_height(table->map_stru->dmaps);

    data2->current_time = get_time();
    data2->frame_id = 0;
    data2->img = NULL;

    table->img = mlx_new_image(table->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!table->img)
    {
        // Handle error (e.g., free resources, exit)
        printf("Error: Failed to create image\n");
        // Cleanup code here
        return 0;
    }
    table->img_data = mlx_get_data_addr(table->img, &table->bpp, &table->size_line, &table->endian);
    if (!table->img_data)
    {
        printf("Error: Failed to get image data address\n");
        mlx_destroy_image(table->mlx, table->img);
        // Cleanup code here
        return 0;
    }

    table->mlx_win = mlx_new_window(table->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");

    mlx_hook(table->mlx_win, 2, 1L << 0, keycode, table);
    mlx_hook(table->mlx_win, 3, 1L << 1, relase_keycode, table);
    mlx_hook(table->mlx_win, 17, 0, close_window, table);
    mlx_loop_hook(table->mlx, mainloop, table);

    mlx_loop(table->mlx);
    return 1;
}