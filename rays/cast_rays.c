#include "../header/cub3d.h"

int has_wall_at_for_ray(t_table *table, double x, double y)
{
    int map_x = (int)(x / TILE_SIZE);
    int map_y = (int)(y / TILE_SIZE);
    if (map_x < 0 || map_x >= table->width || map_y < 0 || map_y >= table->height)
        return 1;
    return table->map_stru->dmaps[map_y][map_x] == '1';
}

/*
** handle baypass between to walls???
*/

int cast_rays(t_table *table, double ray_angle, int columnid)
{
    ray_angle = fmod(ray_angle, 2 * M_PI);
    if (ray_angle < 0)
        ray_angle += 2 * M_PI;

    double xintercept;
	double yintercept;
	double xsteps;
	double ysteps;
    int foundWall = 0;
    double wallHitX = 0;
	double wallHitY = 0;
    int facingup = 0;

    // Horizontal intersection
    int foundHorzWallHit = 0;
    double horzWallHitX = 0;
	double horzWallHitY = 0;
    double horzHitDistance = 1000000;

    // Use pixel coordinates for player position
    double playerX = table->player_coor->position_y * TILE_SIZE;
    double playerY = table->player_coor->position_x * TILE_SIZE;

    yintercept = floor(playerY / TILE_SIZE) * TILE_SIZE;
	if (ray_angle > 0 && ray_angle < M_PI) // FACING DOWN
    	yintercept += TILE_SIZE;
	else // FACING UP
    {
    	yintercept += -0.001;
        facingup = 1;
    }

    xintercept = playerX + (yintercept - playerY) / tan(ray_angle);
	if (ray_angle > 0 && ray_angle < M_PI)
    	ysteps = TILE_SIZE;
	else   
    	ysteps = -TILE_SIZE;

	xsteps = ysteps / tan(ray_angle);

    double nextHorzX = xintercept;
    double nextHorzY = yintercept;

    while (!foundHorzWallHit && nextHorzX >= 0 && nextHorzX < WINDOW_WIDTH &&
           nextHorzY >= 0 && nextHorzY < WINDOW_HEIGHT)
    {
        if (has_wall_at_for_ray(table, nextHorzX, nextHorzY - (facingup ? 1 : 0)))
        {
            foundHorzWallHit = 1;
            horzWallHitX = nextHorzX;
            horzWallHitY = nextHorzY;
            horzHitDistance = sqrt(pow(playerX - horzWallHitX, 2) +
                                   pow(playerY - horzWallHitY, 2));
        }
        else
        {
            nextHorzX += xsteps;
            nextHorzY += ysteps;
        }
    }

    // Vertical intersection
    int foundVertWallHit = 0;
    double vertWallHitX = 0;
	double vertWallHitY = 0;
    double vertHitDistance = 1000000;

    xintercept = floor(playerX / TILE_SIZE) * TILE_SIZE;
	if (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2) // FACING RIGHT
    	xintercept += TILE_SIZE;
	else // FACING LEFT
    	xintercept += -0.001;
    yintercept = playerY + (xintercept - playerX) * tan(ray_angle);
	
	if (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2)
    	xsteps = TILE_SIZE;
	else
    	xsteps = -TILE_SIZE;
    ysteps = xsteps * tan(ray_angle);

    double nextVertX = xintercept;
    double nextVertY = yintercept;
    while (!foundVertWallHit && nextVertX >= 0 && nextVertX < WINDOW_WIDTH &&
           nextVertY >= 0 && nextVertY < WINDOW_HEIGHT)
    {
        if (has_wall_at_for_ray(table, nextVertX, nextVertY))
        {
            foundVertWallHit = 1;
            vertWallHitX = nextVertX;
            vertWallHitY = nextVertY;
            vertHitDistance = sqrt(pow(playerX - vertWallHitX, 2) +
                                   pow(playerY - vertWallHitY, 2));
        }
        else
        {
            nextVertX += xsteps;
            nextVertY += ysteps;
        }
    }

    // Choose closest hit
    if (foundHorzWallHit && horzHitDistance < vertHitDistance)
    {
        wallHitX = horzWallHitX;
        wallHitY = horzWallHitY;
        foundWall = 1;
        table->rays[columnid].wasHitVertical = 0;
        table->rays[columnid].distance = horzHitDistance;
    }
    else if (foundVertWallHit)
    {
        wallHitX = vertWallHitX;
        wallHitY = vertWallHitY;
        foundWall = 1;
        table->rays[columnid].wasHitVertical = 1;
        table->rays[columnid].distance = vertHitDistance;
    }

    table->rays[columnid].rayAngle = ray_angle;
    table->rays[columnid].wallHitX = wallHitX;
    table->rays[columnid].wallHitY = wallHitY;

    // Draw ray if a wall was hit
    if (foundWall)
        draw_line(table, playerX, playerY, wallHitX, wallHitY, 0x00FCF803);

    return 1;
}