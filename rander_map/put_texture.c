#include "../header/cub3d.h"


void draw_line(t_table *table, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        mlx_pixel_put(table->mlx, table->mlx_win, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

int ft_put_player(t_table **data)
{
    t_table *table = *data;
    int color = 0x00FFFFFF;
    int radius = table->player_coor->radius;
    if (radius <= 0 || radius > 16)
        radius = 8;
    int center_x = table->player_coor->position_y * ((*table).height / 2) + 9;
    int center_y = table->player_coor->position_x * ((*table).width / 2) + 9;
    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++)
            if (i * i + j * j <= radius * radius)
                mlx_pixel_put(
                    table->mlx,
                    table->mlx_win,
                    center_x + j,
                    center_y + i,
                    color);
	float line_length = radius * 50; // Line length = 2 * radius
    int line_x = center_x + (int)(cos(table->player_coor->angle) * line_length);
    int line_y = center_y + (int)(sin(table->player_coor->angle) * line_length);
    draw_line(table, center_x, center_y, line_x, line_y, 0x000000FF);
    return 1;
}

int load_images(t_table *table)
{
    table->width = 32;  // Base grid size before halving
    table->height = 32;
    return 1; // No images to load
}

int put_element(t_table *table, char c, int x, int y)
{
    int color = 0x00FF0000;
    int scalx = table->width / 2;
    int scaly = table->height / 2;

    if (c == '1')
    {
        for (int dy = 0; dy < scalx; dy++)
            for (int dx = 0; dx < scaly; dx++)
                mlx_pixel_put(table->mlx, table->mlx_win, y * scaly + dx, x * scalx + dy, color);
    }
    if (c == 'N')
        ft_put_player(&table);
    return 1;
}

int put_texture(t_table *table)
{
    int i = 0;
    int y;

	mlx_clear_window(table->mlx, table->mlx_win);
    if (!load_images(table))
        return 0;
    while (table->map_stru->dmaps[i])
    {
        y = 0;
        while (table->map_stru->dmaps[i][y])
        {
            if (!put_element(table, table->map_stru->dmaps[i][y], i, y))
                return 0;
            y++;
        }
        i++;
    }
    return 1;
}