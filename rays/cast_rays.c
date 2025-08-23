#include "../header/cub3d.h"

int has_wall_at_for_ray(t_table *table, float x, float y)
{
    int map_x = (int)floor(x / TILE_SIZE);
    int map_y = (int)floor(y / TILE_SIZE);

    if (map_x < 0 || map_y < 0)
        return 1;
    if (map_y >= table->height || map_x >= (int)ft_strlen(table->map_stru->dmaps[map_y]))
        return 1;
    if (!table->map_stru || !table->map_stru->dmaps)
        return 1;

    return table->map_stru->dmaps[map_y][map_x] == '1';
}


int find_map_width(char **dmaps)
{
    int max = 0;
    for (int i = 0; dmaps[i]; i++)
    {
        int len = ft_strlen(dmaps[i]);
        if (len > max)
            max = len;
    }
    return max;
}

int cast_rays(t_table *table, float ray_angle, int columnid)
{
    normalize_angle(&ray_angle);
    float playerX = table->player_coor->position_y * TILE_SIZE;
    float playerY = table->player_coor->position_x * TILE_SIZE;

    int foundHorzWallHit = 0;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    float horzHitDistance = 1000000;
    int facingup = ray_angle > M_PI;
    float yintercept = floor(playerY / TILE_SIZE) * TILE_SIZE + (facingup ? -0 : TILE_SIZE);
    float xintercept = playerX + (yintercept - playerY) / tan(ray_angle);
    float ysteps = facingup ? -TILE_SIZE : TILE_SIZE;
    float xsteps = ysteps / tan(ray_angle);
    float nextHorzX = xintercept;
    float nextHorzY = yintercept;

    int max_map_x = table->width = find_map_width(table->map_stru->dmaps) * TILE_SIZE;
    int max_map_y = table->height * TILE_SIZE;

    while (!foundHorzWallHit && nextHorzX >= 0 && nextHorzX < max_map_x && nextHorzY >= 0 && nextHorzY < max_map_y)
    {
        float checkY = nextHorzY + (facingup ? -1 : 0);
        int hitCode = has_wall_at_for_ray(table, nextHorzX, checkY);
        // if (has_wall_at_for_ray(table, nextHorzX, checkY))
        if (hitCode > 0)
        {
            foundHorzWallHit = hitCode;
            horzWallHitX = nextHorzX;
            horzWallHitY = nextHorzY;
            horzHitDistance = sqrt((playerX - horzWallHitX) * (playerX - horzWallHitX) + (playerY - horzWallHitY) * (playerY - horzWallHitY));
            break;
        }
        else
        {
            nextHorzX += xsteps;
            nextHorzY += ysteps;
        }
    }

    int foundVertWallHit = 0;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    float vertHitDistance = 1000000;
    int facingleft = ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2;
    xintercept = floor(playerX / TILE_SIZE) * TILE_SIZE + (facingleft ? -0 : TILE_SIZE);
    yintercept = playerY + (xintercept - playerX) * tan(ray_angle);
    xsteps = facingleft ? -TILE_SIZE : TILE_SIZE;
    ysteps = xsteps * tan(ray_angle);
    float nextVertX = xintercept;
    float nextVertY = yintercept;

    while (!foundVertWallHit && nextVertX >= 0 && nextVertX < max_map_x && nextVertY >= 0 && nextVertY < max_map_y)
    {
        float checkX = nextVertX + (facingleft ? -1 : 0);
        int hitCode = has_wall_at_for_ray(table, checkX, nextVertY);
        // if (has_wall_at_for_ray(table, checkX, nextVertY))
        if (hitCode > 0)
        {
            foundVertWallHit = hitCode;
            vertWallHitX = nextVertX;
            vertWallHitY = nextVertY;
            vertHitDistance = sqrt((playerX - vertWallHitX) * (playerX - vertWallHitX) + (playerY - vertWallHitY) * (playerY - vertWallHitY));
            break;
        }
        else
        {
            nextVertX += xsteps;
            nextVertY += ysteps;
        }
    }

    float wallHitX, wallHitY;
    if (foundHorzWallHit && horzHitDistance < vertHitDistance)
    {
        wallHitX = horzWallHitX;
        wallHitY = horzWallHitY;
        table->rays[columnid].wasHitVertical = 0;
        table->rays[columnid].distance = horzHitDistance;
        table->rays[columnid].hittype = foundHorzWallHit; // wall or door
    }
    else if (foundVertWallHit)
    {
        wallHitX = vertWallHitX;
        wallHitY = vertWallHitY;
        table->rays[columnid].wasHitVertical = 1;
        table->rays[columnid].distance = vertHitDistance;
        table->rays[columnid].hittype = foundVertWallHit;
    }

    else
        return 0;

    table->rays[columnid].rayAngle = ray_angle;
    table->rays[columnid].wallHitX = wallHitX;
    table->rays[columnid].wallHitY = wallHitY;

    // draw_line(table, playerX, playerY, wallHitX, wallHitY, 0x00FCF803);

    return 1;
}
