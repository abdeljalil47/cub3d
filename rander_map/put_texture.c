#include "../header/cub3d.h"

// void put_pixel(t_table *table, int x, int y, int color)
// {
// 	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
// 		char *dst = table->img_data + (y * table->size_line + x * (table->bpp / 8));
// 		*(unsigned int*)dst = color;
// 	}
// }

// void draw_line(t_table *table, int x0, int y0, int x1, int y1, int color)
// {
// 	int dx = abs(x1 - x0);
// 	int dy = abs(y1 - y0);
// 	int sx = x0 < x1 ? 1 : -1;
// 	int sy = y0 < y1 ? 1 : -1;
// 	int err = dx - dy;

// 	while (1)
// 	{
// 		put_pixel(table, x0, y0, color);
// 		if (x0 == x1 && y0 == y1)
// 			break;
// 		int e2 = 2 * err;
// 		if (e2 > -dy)
// 		{
// 			err -= dy;
// 			x0 += sx;
// 		}
// 		if (e2 < dx)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }

// int ft_put_player(t_table **data)
// {
// 	t_table *table = *data;
// 	int color = 0x00FFFFFF;
// 	int radius = table->player_coor->radius;
// 	if (radius <= 0 || radius > 16)
// 		radius = 8; // Re-enable radius check
// 	int center_x = table->player_coor->position_y * MINIMAP_SCALE * TILE_SIZE; // Use position_y for x
// 	int center_y = table->player_coor->position_x * MINIMAP_SCALE * TILE_SIZE; // Use position_x for y
	
// 	for (int i = -radius; i <= radius; i++)
// 	    for (int j = -radius; j <= radius; j++)
// 	        if (i * i + j * j <= radius * radius)
// 	            put_pixel(table, center_x + j, center_y + i, color);
// 	// for (int i = 0; i < TILE_SIZE; i++)
// 	// {
// 	// 	for (int y = 0; y < TILE_SIZE; y++)
// 	// 	{
// 	// 		int pix = y + center_x;
// 	// 		int piy = i + center_y;
// 	// 		put_pixel(table, pix, piy, 0xFF0000FF);
// 	// 	}
// 	// }
	
// 	// double line_length = radius * 40; // Reduced length for better visibility
// 	// double left_angle = table->player_coor->angle - FOV_ANGLE / 2;
// 	// int x = 0;
// 	// while (x < NUM_RAYS)
// 	// {
// 	//     left_angle += FOV_ANGLE / NUM_RAYS;
// 	//     int line_x = center_x + (int)(cos(left_angle) * line_length);
// 	//     int line_y = center_y + (int)(sin(left_angle) * line_length);
// 	//     draw_line(table, center_x, center_y, line_x, line_y, 0x000000FF);
// 	//     x++;
// 	// }
// 	return 1;
// }

// int put_element(t_table *table, char c, int x, int y)
// {
// 	int color = 0x00FF0000;

// 	if (c == '1')
// 	{
// 		for (int dy = 0; dy < MINIMAP_SCALE * TILE_SIZE; dy++)
// 		{
// 			for (int dx = 0; dx < MINIMAP_SCALE * TILE_SIZE; dx++)
// 			{
// 				int pixel_x = y * MINIMAP_SCALE * TILE_SIZE + dx; // y for horizontal, x for vertical to match map
// 				int pixel_y = x * MINIMAP_SCALE * TILE_SIZE + dy; // x for vertical
// 				if (pixel_x >= 0 && pixel_x < WINDOW_WIDTH && pixel_y >= 0 && pixel_y < WINDOW_HEIGHT)
// 					put_pixel(table, pixel_x, pixel_y, color);
// 			}
// 		}
// 	}
// 	return 1;
// }

// int put_texture(t_table *table)
// {
// 	int i = 0;
// 	// int i = table->player_coor->position_x;
// 	int y;

// 	// Clear image buffer
// 	for (int py = 0; py < WINDOW_HEIGHT; py++)
// 		for (int px = 0; px < WINDOW_WIDTH; px++)
// 			put_pixel(table, px, py, 0x000000);

// 	wall_projection(table);

// 	// Draw map
// 	while (table->map_stru->dmaps[i])
// 	{
// 		y = 0;
// 		while (table->map_stru->dmaps[i][y])
// 		{
// 			if (!put_element(table, table->map_stru->dmaps[i][y], i, y))
// 				return 0;
// 			y++;
// 		}
// 		i++;
// 	}
// 	for (int i = 0; i < NUM_RAYS; i++)
// 		if (table->rays[i].wallHitX && table->rays[i].wallHitY)
// 			draw_line(table, table->player_coor->position_y * MINIMAP_SCALE * TILE_SIZE,
// 					  table->player_coor->position_x * MINIMAP_SCALE * TILE_SIZE,
// 					  table->rays[i].wallHitX * MINIMAP_SCALE,
// 					  table->rays[i].wallHitY * MINIMAP_SCALE,
// 					  0x00FCF803);
// 	// Draw player
// 	if (!ft_put_player(&table))
// 		return 0;

// 	// Draw image to window
// 	mlx_put_image_to_window(table->mlx, table->mlx_win, table->img, 0, 0);
// 	return 1;
// }


// General put_pixel for full window (used by wall_projection)
void put_pixel(t_table *table, int x, int y, int color)
{
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        char *dst = table->img_data + (y * table->size_line + x * (table->bpp / 8));
        *(unsigned int*)dst = color;
    }
}

// Minimap-specific put_pixel (clips to 200x200)
void put_pixel_minimap(t_table *table, int x, int y, int color)
{
    if (x >= 0 && x < MINIMAP_SIZE && y >= 0 && y < MINIMAP_SIZE)
    {
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
        put_pixel_minimap(table, x0, y0, color); // Use minimap clipping
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
    int color = 0x000000FF; // White player
    int radius = table->player_coor->radius;
    if (radius <= 0 || radius > 16)
        radius = 8;
    int center_x = MINIMAP_CENTER; // Fixed at 100
    int center_y = MINIMAP_CENTER; // Fixed at 100

    // Draw player as a circle
    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++)
            if (i * i + j * j <= radius * radius)
                put_pixel_minimap(table, center_x + j, center_y + i, color); // Use minimap clipping

	    // Draw single FOV line (middle of FOV, along player_angle)
    int line_length = 18; // Pixels in minimap
    double player_angle = table->player_coor->angle;
    int blue_color = 0x000000FF; // Blue line
    // Calculate endpoint using player_angle
    int end_x = center_x + (int)(cos(player_angle) * line_length);
    int end_y = center_y + (int)(sin(player_angle) * line_length);
    draw_line(table, center_x, center_y, end_x, end_y, blue_color);

    return 1;
}

int put_element(t_table *table, char c, int x, int y)
{
    if (c != '1')
        return 1; // Only draw walls

    int color = 0x00FFFFFF; // Red walls
    // Player's world position in pixels (world coords * tile size)
    double player_px = table->player_coor->position_y * TILE_SIZE;
    double player_py = table->player_coor->position_x * TILE_SIZE;

    // World coordinates of the tile's top-left corner
    int tile_world_x = y * TILE_SIZE; // Map column (y) to world x
    int tile_world_y = x * TILE_SIZE; // Map row (x) to world y

    // Offset relative to player, scaled to minimap
    int offset_x = (tile_world_x - player_px) * MINIMAP_SCALE;
    int offset_y = (tile_world_y - player_py) * MINIMAP_SCALE;

    // Map to minimap coordinates (center player at 100,100)
    int start_x = MINIMAP_CENTER + offset_x;
    int start_y = MINIMAP_CENTER + offset_y;

    // Draw scaled tile
    int scaled_tile = (int)(TILE_SIZE * MINIMAP_SCALE);
    for (int dy = 0; dy < scaled_tile; dy++)
    {
        for (int dx = 0; dx < scaled_tile; dx++)
        {
            int pixel_x = start_x + dx;
            int pixel_y = start_y + dy;
            put_pixel_minimap(table, pixel_x, pixel_y, color); // Use minimap clipping
        }
    }
    return 1;
}

int put_texture(t_table *table)
{
    // Clear minimap region
    for (int py = 0; py < MINIMAP_SIZE; py++)
        for (int px = 0; px < MINIMAP_SIZE; px++)
            put_pixel_minimap(table, px, py, 0x000000); // Black background

    // Draw map
    int i = 0;
    wall_projection(table);
    while (table->map_stru->dmaps[i])
    {
        int y = 0;
        while (table->map_stru->dmaps[i][y])
        {
            put_element(table, table->map_stru->dmaps[i][y], i, y);
            y++;
        }
        i++;
    }

    // Draw rays
    // double player_px = table->player_coor->position_y * TILE_SIZE;
    // double player_py = table->player_coor->position_x * TILE_SIZE;
    // for (int i = 0; i < NUM_RAYS; i++)
    // {
    //     if (table->rays[i].wallHitX && table->rays[i].wallHitY)
    //     {
    //         int ray_x = MINIMAP_CENTER + (table->rays[i].wallHitX - player_px) * MINIMAP_SCALE;
    //         int ray_y = MINIMAP_CENTER + (table->rays[i].wallHitY - player_py) * MINIMAP_SCALE;
    //         draw_line(table, MINIMAP_CENTER, MINIMAP_CENTER, ray_x, ray_y, 0x00FCF803);
    //     }
    // }

    // Draw player
    ft_put_player(&table);

    // Render 3D walls

    // Draw image to window
    mlx_put_image_to_window(table->mlx, table->mlx_win, table->img, 0, 0);
    return 1;
}