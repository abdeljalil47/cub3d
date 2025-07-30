#include "../header/cub3d.h"

void put_pixel(t_table *table, int x, int y, int color)
{
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
        char *dst = table->img_data + (y * table->size_line + x * (table->bpp / 8));
        *(unsigned int*)dst = color;
    }
}

void draw_line(t_table *table, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        put_pixel(table, x0, y0, color);
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
        radius = 8; // Re-enable radius check
    int center_x = table->player_coor->position_y * MINIMAP_SCALE * TILE_SIZE; // Use position_y for x
    int center_y = table->player_coor->position_x * MINIMAP_SCALE * TILE_SIZE; // Use position_x for y
    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++)
            if (i * i + j * j <= radius * radius)
                put_pixel(table, center_x + j, center_y + i, color);
    // float line_length = radius * 40; // Reduced length for better visibility
    // double left_angle = table->player_coor->angle - FOV_ANGLE / 2;
    // int x = 0;
    // while (x < NUM_RAYS)
    // {
    //     left_angle += FOV_ANGLE / NUM_RAYS;
    //     int line_x = center_x + (int)(cos(left_angle) * line_length);
    //     int line_y = center_y + (int)(sin(left_angle) * line_length);
    //     draw_line(table, center_x, center_y, line_x, line_y, 0x000000FF);
    //     x++;
    // }
    return 1;
}

int put_element(t_table *table, char c, int x, int y)
{
    int color = 0x00FF0000;

    if (c == '1')
    {
        for (int dy = 0; dy < MINIMAP_SCALE * TILE_SIZE; dy++)
        {
            for (int dx = 0; dx < MINIMAP_SCALE * TILE_SIZE; dx++)
            {
                int pixel_x = y * MINIMAP_SCALE * TILE_SIZE + dx; // y for horizontal, x for vertical to match map
                int pixel_y = x * MINIMAP_SCALE * TILE_SIZE + dy; // x for vertical
                if (pixel_x >= 0 && pixel_x < WINDOW_WIDTH && pixel_y >= 0 && pixel_y < WINDOW_HEIGHT)
                    put_pixel(table, pixel_x, pixel_y, color);
            }
        }
    }
    return 1;
}


int put_texture(t_table *table)
{
    int i = 0;
    int y;

    // Clear image buffer
    for (int py = 0; py < WINDOW_HEIGHT; py++)
        for (int px = 0; px < WINDOW_WIDTH; px++)
            put_pixel(table, px, py, 0x000000);

    wall_projection(table);

    // Draw map
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
    for (int i = 0; i < NUM_RAYS; i++)
        if (table->rays[i].wallHitX && table->rays[i].wallHitY)
            draw_line(table, table->player_coor->position_y * MINIMAP_SCALE * TILE_SIZE,
                      table->player_coor->position_x * MINIMAP_SCALE * TILE_SIZE,
                      table->rays[i].wallHitX * MINIMAP_SCALE,
                      table->rays[i].wallHitY * MINIMAP_SCALE,
                      0x00FCF803);
    // Draw player
    if (!ft_put_player(&table))
        return 0;

    // Draw image to window
    mlx_put_image_to_window(table->mlx, table->mlx_win, table->img, 0, 0);
    return 1;
}