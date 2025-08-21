#include "../header/cub3d.h"

int find_ceiling_floor(t_table *table, char type)
{
    int ceiling;
    int floor;

    map_valid *map = table->map_ele;
    while (map)
    {
        if (ft_strcmp(map->type, "F") == 0)
            floor = map->color_rgb;
        else if (ft_strcmp(map->type, "C") == 0)
            ceiling = map->color_rgb;
        map = map->next;
    }
    if (type == 'C')
        return (ceiling);
    return (floor);
}
void find_texture_wall_angle(t_table *table)
{
    map_valid *wall = table->map_ele;
    while (wall)
    {
        if ((ft_strcmp(wall->type, "NO") == 0) || (ft_strcmp(wall->type, "N") == 0))
            table->tex_path.NO = wall->path;
        else if ((ft_strcmp(wall->type, "SO") == 0) || (ft_strcmp(wall->type, "S") == 0))
            table->tex_path.SO = wall->path;
        else if ((ft_strcmp(wall->type, "WE") == 0) || (ft_strcmp(wall->type, "W") == 0))
            table->tex_path.WE = wall->path;
        else if ((ft_strcmp(wall->type, "EA") == 0) || (ft_strcmp(wall->type, "E") == 0))
            table->tex_path.EA = wall->path;
        wall = wall->next;
    }
}
int get_texture_pixel(t_texture *texture, int tex_x, int tex_y)
{
    if (tex_x < 0 || tex_x >= texture->width || tex_y < 0 || tex_y >= texture->height)
        return 0;
    int index = (tex_y * texture->size_line) + (tex_x * (texture->bpp / 8));
    return *(int *)(texture->data + index);
}
char *ft_my_strcat(char *dest, int num, char *src)
{
    int a = 0;
    while (dest[a])
        a++;

    int num_copy = num;
    int num_len = (num == 0) ? 1 : 0;
    while (num_copy)
    {
        num_copy /= 10;
        num_len++;
    }

    int b = 0;
    while (src[b])
        b++;

    int total = a + num_len + b + 1;
    char *res_path = malloc(total);
    if (!res_path)
        return NULL;

    int c = 0;
    while (c < a)
    {
        res_path[c] = dest[c];
        c++;
    }

    int i = num_len - 1;
    int temp_num = num;
    while (i >= 0)
    {
        res_path[c + i] = (temp_num % 10) + '0';
        temp_num /= 10;
        i--;
    }
    c += num_len;

    int j = 0;
    while (j < b)
    {
        res_path[c + j] = src[j];
        j++;
    }

    res_path[total - 1] = '\0';
    return res_path;
}

t_texture hand_frames[HAND_FRAMES_KNIFE];
t_texture hand_frames_mv[HAND_FRAMES_KNIFE_MV];

char **hand_path_frames(t_hand_anim *hand, char *type_mv)
{
    int i = 0;
    if (ft_strcmp(type_mv, "KNIFE") == 0)
    {
        while (i < HAND_FRAMES_KNIFE)
        {
            char *path = ft_my_strcat("./texture/hand/", i + 1, ".xpm");
            hand->hand_paths[i] = ft_strdup(path);
            free(path);
            i++;
        }
        return hand->hand_paths;
    }
    if (ft_strcmp(type_mv, "KNIFE_MV") == 0)
    {
        i = 0;
        while (i < HAND_FRAMES_KNIFE_MV)
        {
            char *path = ft_my_strcat("./texture/hand1/", i + 1, ".xpm");
            hand->hand_paths_mv[i] = ft_strdup(path);
            free(path);
            i++;
        }
        return hand->hand_paths_mv;
    }
    return NULL;
}

void draw_hand(t_table *table)
{
    t_texture *hand;
    int max_frames;
    float scale_factor = 0.7;

    if (table->hand_anim.flag)
    {
        hand = &hand_frames_mv[table->hand_anim.current_frame];
        max_frames = HAND_FRAMES_KNIFE_MV;
    }
    else
    {
        hand = &hand_frames[table->hand_anim.current_frame];
        max_frames = HAND_FRAMES_KNIFE;
    }

    int scaled_width = (int)(hand->width * scale_factor);
    int scaled_height = (int)(hand->height * scale_factor);

    int start_x = WINDOW_WIDTH / 2 - scaled_width / 2;
    int start_y = WINDOW_HEIGHT - scaled_height;
    for (int y = 0; y < scaled_height; y++)
    {
        for (int x = 0; x < scaled_width; x++)
        {
            int tex_x = (int)(x / scale_factor);
            int tex_y = (int)(y / scale_factor);
            int color = get_texture_pixel(hand, tex_x, tex_y);
            if ((color & 0x00FFFFFF) != 0x000000)
                put_pixel(table, start_x + x, start_y + y, color);
        }
    }
    if (table->hand_anim.flag && table->hand_anim.current_frame == HAND_FRAMES_KNIFE_MV - 1)
    {
        table->hand_anim.flag = false;
        table->hand_anim.current_frame = 0;
        table->hand_anim.anim_counter = 0;
        return;
    }
    table->hand_anim.anim_counter++;
    if (table->hand_anim.anim_counter >= HAND_ANIM_SPEED)
    {
        table->hand_anim.current_frame++;
        if (table->hand_anim.current_frame >= max_frames)
        {
            table->hand_anim.current_frame = 0;
            if (table->hand_anim.flag)
                table->hand_anim.flag = false;
        }
        table->hand_anim.anim_counter = 0;
    }
}

int weapon(t_table *table, char *type_mv)
{
    static int loaded_knife = 0;
    static int loaded_knife_mv = 0;
    char **hand_paths = hand_path_frames(&table->hand_anim, type_mv);
    int i = 0;
    t_texture *frames = NULL;
    int max_frames = 0;

    if (ft_strcmp(type_mv, "KNIFE") == 0)
    {
        if (loaded_knife)
            return 0;
        frames = hand_frames;
        max_frames = HAND_FRAMES_KNIFE;
        loaded_knife = 1;
    }
    else if (ft_strcmp(type_mv, "KNIFE_MV") == 0)
    {
        if (loaded_knife_mv)
            return 0;
        frames = hand_frames_mv;
        max_frames = HAND_FRAMES_KNIFE_MV;
        loaded_knife_mv = 1;
    }

    while (i < max_frames)
    {
        frames[i].img = mlx_xpm_file_to_image(table->mlx, hand_paths[i], &frames[i].width, &frames[i].height);
        if (!frames[i].img)
            return -1;
        frames[i].data = mlx_get_data_addr(frames[i].img, &frames[i].bpp, &frames[i].size_line, &frames[i].endian);
        if (!frames[i].data)
        {
            mlx_destroy_image(table->mlx, frames[i].img);
            return -1;
        }
        i++;
    }
    return 0;
}

void load_textures(t_table *table)
{
    int i = 0;
    table->textures[0].img = mlx_xpm_file_to_image(table->mlx, table->tex_path.NO,
                                                   &table->textures[0].width, &table->textures[0].height);
    table->textures[1].img = mlx_xpm_file_to_image(table->mlx, table->tex_path.SO,
                                                   &table->textures[1].width, &table->textures[1].height);
    table->textures[2].img = mlx_xpm_file_to_image(table->mlx, table->tex_path.WE,
                                                   &table->textures[2].width, &table->textures[2].height);
    table->textures[3].img = mlx_xpm_file_to_image(table->mlx, table->tex_path.EA,
                                                   &table->textures[3].width, &table->textures[3].height);
    table->textures[4].img = mlx_xpm_file_to_image(table->mlx, "/mnt/homes/abdsebba/Desktop/untitled folder/texture/door.xpm",
                                                   &table->textures[4].width, &table->textures[4].height);
    while (i < 5)
    {
        if (!table->textures[i].img)
            continue;
        table->textures[i].data = mlx_get_data_addr(table->textures[i].img,
                                                    &table->textures[i].bpp, &table->textures[i].size_line, &table->textures[i].endian);
        i++;
    }
}

int wall_projection(t_table *table)
{
    int i = 0;
    find_texture_wall_angle(table);
    load_textures(table);
    float distance_project = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);

    while (i < NUM_RAYS)
    {
        float ray_angle = table->rays[i].rayAngle;
        float corrected_distance = table->rays[i].distance * cos(ray_angle - table->player_coor->angle);
        if (corrected_distance < 0.1)
            corrected_distance = 0.1;
        float wall_stripheight = (TILE_SIZE / corrected_distance) * distance_project;
        int top_pixel = (int)(WINDOW_HEIGHT / 2 - wall_stripheight / 2);
        int bottom_pixel = (int)(WINDOW_HEIGHT / 2 + wall_stripheight / 2);
        if (top_pixel < 0)
            top_pixel = 0;
        if (bottom_pixel >= WINDOW_HEIGHT)
            bottom_pixel = WINDOW_HEIGHT - 1;

        t_texture *texture;
        float wall_hit;
        int flip_x;
        if (table->rays[i].hittype == 2) // door was hit
        {
            if (table->open_door == 0)
            {
                if (table->rays[i].wasHitVertical)
                    wall_hit = table->rays[i].wallHitY;
                else
                    wall_hit = table->rays[i].wallHitX;
                texture = &table->textures[4]; // door texture
                flip_x = 0;
            }
            else
            {
                i++;
                continue;
            }
        }
        else
        {
            if (table->rays[i].wasHitVertical)
            {
                wall_hit = table->rays[i].wallHitY;
                if (ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2)
                {
                    texture = &table->textures[2];
                    flip_x = 1;
                }
                else
                {
                    texture = &table->textures[3];
                    flip_x = 0;
                }
            }
            else
            {
                wall_hit = table->rays[i].wallHitX;
                if (ray_angle > M_PI)
                {
                    texture = &table->textures[1];
                    flip_x = 1;
                }
                else
                {
                    texture = &table->textures[0];
                    flip_x = 0;
                }
            }
        }

        int tex_x = (int)(wall_hit / TILE_SIZE * texture->width) % texture->width;
        if (flip_x)
            tex_x = texture->width - tex_x - 1;
        if (tex_x < 0)
            tex_x += texture->width;

        float step = (float)texture->height / wall_stripheight;
        float tex_pos = (top_pixel - WINDOW_HEIGHT / 2 + wall_stripheight / 2) * step;

        int y = 0;
        while (y < WINDOW_HEIGHT)
        {
            int x = i * WALL_STRIP_WIDTH;
            while (x < (i + 1) * WALL_STRIP_WIDTH)
            {
                if (y < top_pixel)
                    put_pixel(table, x, y, find_ceiling_floor(table, 'C'));
                else if (y >= top_pixel && y <= bottom_pixel)
                {
                    int tex_y = (int)tex_pos;
                    if (tex_y >= texture->height)
                        tex_y = texture->height - 1;
                    tex_pos += step;
                    int color = get_texture_pixel(texture, tex_x, tex_y);
                    // if (table->open_door == 1)
                    // {
                    //     color = get_texture_pixel(texture, tex_x, tex_y);
                    // }
                    put_pixel(table, x, y, color);
                }
                else
                    put_pixel(table, x, y, find_ceiling_floor(table, 'F'));
                x++;
            }
            y++;
        }
        i++;
    }
    draw_hand(table);
    return 1;
}
