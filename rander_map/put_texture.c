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
	
// 	// float line_length = radius * 40; // Reduced length for better visibility
// 	// float left_angle = table->player_coor->angle - FOV_ANGLE / 2;
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
// 	for (int py = 0; py < WINDOW_HEIGHT; py++)
// 		for (int px = 0; px < WINDOW_WIDTH; px++)
// 			put_pixel(table, px, py, 0x000000);

// 	// wall_projection(table);

// 	for (int i = 0; table->map_stru->dmaps[i]; i++)
// 		for (int y = 0; table->map_stru->dmaps[i][y]; y++)
// 			put_element(table, table->map_stru->dmaps[i][y], i, y);

// 	for (int i = 0; i < NUM_RAYS; i++)
// 	{
// 		if (table->rays[i].wallHitX && table->rays[i].wallHitY)
// 		{
// 			int player_x = table->player_coor->position_y * MINIMAP_SCALE * TILE_SIZE;
// 			int player_y = table->player_coor->position_x * MINIMAP_SCALE * TILE_SIZE;

// 			int ray_x = (table->rays[i].wallHitX / TILE_SIZE) * MINIMAP_SCALE * TILE_SIZE;
// 			int ray_y = (table->rays[i].wallHitY / TILE_SIZE) * MINIMAP_SCALE * TILE_SIZE;

// 			draw_line(table, player_x, player_y, ray_x, ray_y, 0x00FCF803);
// 		}
// 	}

// 	if (!ft_put_player(&table))
// 		return 0;

// 	mlx_put_image_to_window(table->mlx, table->mlx_win, table->img, 0, 0);
// 	return 1;
// }



// // General put_pixel for full window (used by wall_projection)
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
int get_inverse_color(int color, char type)
{
    int r = 0;
    int g = 0;
    int b = 0;
    if(type == 'M')
    {
        r = 255 - ((color >> 16) & 0xFF);
        g = 255 - ((color >> 8) & 0xFF);
        b = 255 - (color & 0xFF);
    }
      else if (type == 'P')
    {
        int temp = r;
        r = (b + 100) % 256;
        g = (g + 60) % 256;
        b = (temp + 30) % 256;
    }
    return (r << 16) | (g << 8) | b;
}


int ft_put_player(t_table **data)
{
    // printf("\033[0;32m-------->>%d\033[0m\n", (*data)->open_door);
    t_table *table = *data;
    int color = get_inverse_color(find_ceiling_floor(table, 'C'), 'P');
    int radius = table->player_coor->radius;
    if (radius <= 0 || radius > 16)
        radius = 8;
    int center_x = MINIMAP_CENTER;
    int center_y = MINIMAP_CENTER;

    for (int i = -radius; i <= radius; i++)
        for (int j = -radius; j <= radius; j++)
            if (i * i + j * j <= radius * radius)
                put_pixel_minimap(table, center_x + j, center_y + i, color); 

    int line_length = 18;
    float player_angle = table->player_coor->angle;
    int blue_color = get_inverse_color(find_ceiling_floor(table, 'C'), 'P');
    int end_x = center_x + (int)(cos(player_angle) * line_length);
    int end_y = center_y + (int)(sin(player_angle) * line_length);
    draw_line(table, center_x, center_y, end_x, end_y, blue_color);

    return 1;
}
void draw_minimap_background(t_table *table)
{
    for (int py = 0; py < MINIMAP_SIZE; py++)
    {
        for (int px = 0; px < MINIMAP_SIZE; px++)
        {
            put_pixel_minimap(table, px, py, 0x607ea6); // black background
        }
    }
}

int put_element(t_table *table, char c, int x, int y)
{
    int color;

    if (c == 'D')
    {
        color = 0xFFEA00; 
        table->door_exist = true; 
    }
    else if (c == '1')
        color = get_inverse_color(find_ceiling_floor(table, 'C'), 'M');
    else
        return 1;
    float player_px = table->player_coor->position_y * TILE_SIZE;
    float player_py = table->player_coor->position_x * TILE_SIZE;

    int tile_world_x = y * TILE_SIZE; 
    int tile_world_y = x * TILE_SIZE; 

    int offset_x = (tile_world_x - player_px) * MINIMAP_SCALE;
    int offset_y = (tile_world_y - player_py) * MINIMAP_SCALE;

    int start_x = MINIMAP_CENTER + offset_x;
    int start_y = MINIMAP_CENTER + offset_y;
    int scaled_tile = (int)(TILE_SIZE * MINIMAP_SCALE);
    for (int dy = 0; dy < scaled_tile; dy++)
    {
        for (int dx = 0; dx < scaled_tile; dx++)
        {
            int pixel_x = start_x + dx;
            int pixel_y = start_y + dy;
            put_pixel_minimap(table, pixel_x, pixel_y, color);
        }
    }

    return 1;
}

int put_texture(t_table *table)
{
    for (int py = 0; py < MINIMAP_SIZE; py++)
        for (int px = 0; px < MINIMAP_SIZE; px++)
            put_pixel_minimap(table, px, py, 0x000000);

    int i = 0;
    wall_projection(table);
    draw_minimap_background(table);//draw the background of the map
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

    // float player_px = table->player_coor->position_y * TILE_SIZE;
    // float player_py = table->player_coor->position_x * TILE_SIZE;
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