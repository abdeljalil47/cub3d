#include "../header/cub3d.h"

// int	wall_projection(t_table *table)
// {
// 	int		i;
// 	double	ray_distance;
// 	double	distance_project;
// 	double	wall_stripheight;
// 	int		floor;
// 	int		ceiling;
// 	t_ray	ray;

// 	distance_project = (WINDOW_WIDTH / 2) / (tan(FOV_ANGLE / 2));
// 	i = 0;
// 	map_valid *map = table->map_ele;
// 	while (map)
// 	{
// 		if (ft_strcmp(map->type, "F") == 0)
// 			floor = map->color_rgb;
// 		if (ft_strcmp(map->type, "C") == 0)
// 			ceiling = map->color_rgb;
// 		map = map->next;
// 	}
// 	while (i < NUM_RAYS)
// 	{
// 		ray = table->rays[i];

// 		ray_distance = ray.distance * cos(ray.rayAngle - table->player_coor->angle);
// 		wall_stripheight = (TILE_SIZE / ray_distance) * distance_project;

// 		// draw_line(
// 		// 		table,
// 		// 		i * WALL_STRIP_WIDTH,
// 		// 		(WINDOW_HEIGHT / 2) - (wall_stripheight / 2),
// 		// 		WALL_STRIP_WIDTH,
// 		// 		wall_stripheight,
// 		// 		0xFFFFFF);

// 		int top_pixel = (WINDOW_HEIGHT / 2) - (wall_stripheight / 2);
// 		int bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_stripheight / 2);
// 		for (int x = i * WALL_STRIP_WIDTH; x < (i + 1) * WALL_STRIP_WIDTH; x++)
// 			for (int y = top_pixel; y <= bottom_pixel; y++)
// 				put_pixel(table, x, y, 0xFFFFFF); // White walls
// 		i++;
// 	}
// 	return 1;
// }

int wall_projection(t_table *table)
{
	int		floor;
	int		ceiling;
	map_valid *map = table->map_ele;
	while (map)
	{
		if (ft_strcmp(map->type, "F") == 0)
			floor = map->color_rgb;
		if (ft_strcmp(map->type, "C") == 0)
			ceiling = map->color_rgb;
		map = map->next;
	}
    double distance_project = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2); // Projection plane distance
    for (int i = 0; i < NUM_RAYS; i++)
    {
        // Correct distance for fisheye effect
        double ray_angle = table->rays[i].rayAngle;
        double corrected_distance = table->rays[i].distance * cos(ray_angle - table->player_coor->angle);
        if (corrected_distance < 0.1) // Avoid division by near-zero
            corrected_distance = 0.1;

        // Calculate wall strip height
        double wall_stripheight = (TILE_SIZE / corrected_distance) * distance_project;
        int top_pixel = (int)(WINDOW_HEIGHT / 2 - wall_stripheight / 2);
        int bottom_pixel = (int)(WINDOW_HEIGHT / 2 + wall_stripheight / 2);

        // Clamp to window bounds
        if (top_pixel < 0)
            top_pixel = 0;
        if (bottom_pixel >= WINDOW_HEIGHT)
            bottom_pixel = WINDOW_HEIGHT - 1;

        // Choose color based on hit type
        int color = 0xFF0000;//table->rays[i].wasHitVertical ? 0x00FF0000 : 0x00808080; // Red for vertical, gray for horizontal

        // Draw ceiling, wall, and floor for this strip
        for (int y = 0; y < WINDOW_HEIGHT; y++)
        {
            for (int x = i * WALL_STRIP_WIDTH; x < (i + 1) * WALL_STRIP_WIDTH; x++)
            {
                if (y < top_pixel)
                    put_pixel(table, x, y, ceiling); // Ceiling (gray)
                else if (y >= top_pixel && y <= bottom_pixel)
                    put_pixel(table, x, y, color); // Wall
                else
                    put_pixel(table, x, y, floor); // Floor (black)
            }
        }
    }
    return 1;
}