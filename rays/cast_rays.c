#include "../header/cub3d.h"

int has_wall_at_for_ray(t_table *table, double x, double y)
{
    int map_x = (int)floor(x / TILE_SIZE);
    int map_y = (int)floor(y / TILE_SIZE);

    // Enhanced boundary check with logging
    if (map_x < 0 || map_x >= table->width || map_y < 0 || map_y >= table->height || map_x > (int)ft_strlen(table->map_stru->dmaps[map_y]))
    {
        printf("Out-of-bounds access detected: map_x=%d, map_y=%d (width=%d, height=%d)\n",
               map_x, map_y, table->width, table->height);
        return 1; // Treat out-of-bounds as a wall
    }

    printf("\t\t\t\t%d\n", map_x);
    printf("\t\t\t\t%d\n", map_y);

    // Ensure dmaps is not null
    if (!table->map_stru || !table->map_stru->dmaps)
    {
        printf("Error: dmaps is null\n");
        return 1;
    }

    return table->map_stru->dmaps[map_y][map_x] == '1';
}

/*
** handle bypass between two walls???
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

    // Horizontal intersection
    yintercept = floor(playerY / TILE_SIZE) * TILE_SIZE;
    if (ray_angle > 0 && ray_angle < M_PI) // FACING DOWN
        yintercept += TILE_SIZE;
    else // FACING UP
    {
        yintercept -= 0.001; // Small epsilon to avoid tile boundary issues
        facingup = 1;
    }

    xintercept = playerX + (yintercept - playerY) * cos(ray_angle) / sin(ray_angle);
    ysteps = (ray_angle > 0 && ray_angle < M_PI) ? TILE_SIZE : -TILE_SIZE;
    xsteps = ysteps * cos(ray_angle) / sin(ray_angle);

    double nextHorzX = xintercept;
    double nextHorzY = yintercept;

    // Use map grid boundaries instead of window boundaries
    int max_map_x = table->width * TILE_SIZE;
    int max_map_y = table->height * TILE_SIZE;

    while (!foundHorzWallHit && nextHorzX >= 0 && nextHorzX < max_map_x &&
           nextHorzY >= 0 && nextHorzY < max_map_y)
    {
        double checkY = nextHorzY - (facingup ? 0.001 : 0); // Adjusted to avoid boundary issues
        if (has_wall_at_for_ray(table, nextHorzX, checkY))
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
        xintercept -= 0.001;

    yintercept = playerY + (xintercept - playerX) * sin(ray_angle) / cos(ray_angle);
    xsteps = (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2) ? TILE_SIZE : -TILE_SIZE;
    ysteps = xsteps * sin(ray_angle) / cos(ray_angle);

    double nextVertX = xintercept;
    double nextVertY = yintercept;

    while (!foundVertWallHit && nextVertX >= 0 && nextVertX < max_map_x &&
           nextVertY >= 0 && nextVertY < max_map_y)
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
