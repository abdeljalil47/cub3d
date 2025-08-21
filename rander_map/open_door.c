#include "../header/cub3d.h"

// int open_door(t_table *table)
// {
//     player *player;

//     int x_position1;
//     int y_position1;

//     player = table->player_coor;
//     y_position1 = (int)(player->position_x);
//     x_position1 = (int)(player->position_y);

//     printf("{{hni bdatii}}\n");
//     float move_step = 1 * 52;
//     float new_x = player->position_y * TILE_SIZE;
//     float new_y = player->position_x * TILE_SIZE;

//     float move_angle = table->player_coor->angle;
//     if (move_step < 0)
//         move_angle += M_PI;
//     new_x += cos(move_angle) * fabs(move_step);
//     new_y += sin(move_angle) * fabs(move_step);
//     printf("%f\n", new_x);
//     printf("%f\n", new_y);
//     int map_x = floor(new_x / TILE_SIZE);
//     int map_y = floor(new_y / TILE_SIZE);

//     if (map_x < 0 || map_y < 0)
//         return 1;
//     if (map_x >= table->width || map_y >= table->height)
//         return 1;
//     if (table->map_stru->dmaps[map_y][map_x] == '1')
//         return 1;
//     player->position_y = new_x / TILE_SIZE;
//     player->position_x = new_y / TILE_SIZE;
//     table->open_door = 1;
//     table->open_door = 0;
//     return 0;
// }

int open_door(t_table *table)
{
    player *p = table->player_coor;
    float move_step = 0.5f;
    float move_angle = p->angle;

    float front_x = p->position_x + cos(move_angle) * move_step;
    float front_y = p->position_y + sin(move_angle) * move_step;

    int map_x = floor(front_x);
    int map_y = floor(front_y);

    if (map_x < 0 || map_y < 0 || map_x >= table->width || map_y >= table->height)
        return 1;

    char *cell = &table->map_stru->dmaps[map_y][map_x];

    float dist = sqrtf((p->position_x - (map_x + 0.5f)) * (p->position_x - (map_x + 0.5f)) +
                       (p->position_y - (map_y + 0.5f)) * (p->position_y - (map_y + 0.5f)));

    if (dist <= 1.0f)
    {
        if (*cell == 'D')
        {
            *cell = '0';
            table->open_door = 1;
        }
        else if (*cell == '0')
        {
            *cell = 'D';
            table->open_door = 0;
        }
        return 0;
    }

    return 1;
}
