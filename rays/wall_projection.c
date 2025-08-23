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
    if (!table || !table->map_ele)
        return;
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

char	*ft_my_strcat(char *dest, int num, char *src)
{
	int		i;
	int		j;
	int		dest_len;
	int		num_len;
	int		src_len;
	char	*res;
	int		tmp;

	dest_len = 0;
	while (dest[dest_len])
		dest_len++;

	num_len = (num == 0) ? 1 : 0;
	tmp = num;
	while (tmp)
	{
		tmp /= 10;
		num_len++;
	}

	src_len = 0;
	while (src[src_len])
		src_len++;

	res = malloc(dest_len + num_len + src_len + 1);
	if (!res)
		return (NULL);

	i = 0;
	while (i < dest_len)
	{
		res[i] = dest[i];
		i++;
	}

	tmp = num;
	j = num_len - 1;
	while (j >= 0)
	{
		res[i + j] = (tmp % 10) + '0';
		tmp /= 10;
		j--;
	}
	i += num_len;

	j = 0;
	while (j < src_len)
	{
		res[i + j] = src[j];
		j++;
	}
	res[i + j] = '\0';

	return (res);
}

static void	free_paths(char **paths, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		free(paths[i]);
		i++;
	}
}

char	**hand_path_frames(t_hand_anim *hand, char *type_mv)
{
	int		i;
	char	*path;

	i = 0;
	if (ft_strcmp(type_mv, "KNIFE") == 0)
	{
		while (i < HAND_FRAMES_KNIFE)
		{
			path = ft_my_strcat("./texture/hand/", i + 1, ".xpm");
			if (!path)
				return free_paths(hand->hand_paths, i), NULL;
			hand->hand_paths[i] = ft_strdup(path);
			free(path);
			if (!hand->hand_paths[i])
				return free_paths(hand->hand_paths, i), NULL;
			i++;
		}
		return hand->hand_paths;
	}
	if (ft_strcmp(type_mv, "KNIFE_MV") == 0)
	{
		while (i < HAND_FRAMES_KNIFE_MV)
		{
			path = ft_my_strcat("./texture/hand1/", i + 1, ".xpm");
			if (!path)
				return free_paths(hand->hand_paths_mv, i), NULL;
			hand->hand_paths_mv[i] = ft_strdup(path);
			free(path);
			if (!hand->hand_paths_mv[i])
				return free_paths(hand->hand_paths_mv, i), NULL;
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
    float scale_x = (WINDOW_WIDTH / 1000.0f);
    float scale_y = (WINDOW_HEIGHT / 1200.0f);
    float scale_factor = ((scale_x < scale_y) ? scale_x : scale_y) * 0.7f;

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

    int y = 0;
    while (y < scaled_height)
    {
        int x = 0;
        while (x < scaled_width)
        {
            int tex_x = (int)(x / scale_factor);
            int tex_y = (int)(y / scale_factor);
            int color = get_texture_pixel(hand, tex_x, tex_y);
            if ((color & 0x00FFFFFF) != 0x000000)
                put_pixel(table, start_x + x, start_y + y, color);
            x++;
        }
        y++;
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
    if (!hand_paths)
        return 1;

    t_texture *frames = NULL;
    int max_frames = 0;
    int i = 0;

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
    else
        return 1;

    while (i < max_frames)
    {
        frames[i].img = mlx_xpm_file_to_image(table->mlx, hand_paths[i], &frames[i].width, &frames[i].height);
        if (!frames[i].img)
            return 1;
        frames[i].data = mlx_get_data_addr(frames[i].img, &frames[i].bpp, &frames[i].size_line, &frames[i].endian);
        if (!frames[i].data)
        {
            mlx_destroy_image(table->mlx, frames[i].img);
            return 1;
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

    i = 0;
    while (i < 4)
    {
        if (!table->textures[i].img)
        {
            int j = 0;
            while (j < i)
            {
                mlx_destroy_image(table->mlx, table->textures[j].img);
                j++;
            }
            return;
        }
        table->textures[i].data = mlx_get_data_addr(table->textures[i].img,
                                                    &table->textures[i].bpp, &table->textures[i].size_line, &table->textures[i].endian);
        if (!table->textures[i].data)
        {
            int j = 0;
            while (j <= i)
            {
                mlx_destroy_image(table->mlx, table->textures[j].img);
                j++;
            }
            return;
        }
        i++;
    }
}

int get_texture_pixel(t_texture *texture, int tex_x, int tex_y)
{
    if (!texture || !texture->data)
        return 0;
    if (tex_x < 0 || tex_x >= texture->width || tex_y < 0 || tex_y >= texture->height)
        return 0;

    int bytes_per_pixel = texture->bpp / 8;
    int index = (tex_y * texture->size_line) + (tex_x * bytes_per_pixel);

    if (bytes_per_pixel == 4)
        return *(int *)(texture->data + index);
    else if (bytes_per_pixel == 3)
    {
        unsigned char *p = (unsigned char *)(texture->data + index);
        return (p[0] << 16) | (p[1] << 8) | p[2];
    }
    return 0;
}


int wall_projection(t_table *table)
{
    if (!table)
        return -1;
    find_texture_wall_angle(table);
    load_textures(table);
    for (int i = 0; i < 4; i++)
        if (!table->textures[i].img || !table->textures[i].data)
            return -1;

    int i = 0;
    float distance_project = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);

    while (i < NUM_RAYS)
    {
        float ray_angle = table->rays[i].rayAngle;
        float corrected_distance = table->rays[i].distance * cos(ray_angle - table->player_coor->angle);
        if (corrected_distance < 0.1f)
            corrected_distance = 0.1f;
        float wall_stripheight = (TILE_SIZE / corrected_distance) * distance_project;
        int top_pixel = (int)(WINDOW_HEIGHT / 2 - wall_stripheight / 2);
        int bottom_pixel = (int)(WINDOW_HEIGHT / 2 + wall_stripheight / 2);
        if (top_pixel < 0)
            top_pixel = 0;
        if (bottom_pixel >= WINDOW_HEIGHT)
            bottom_pixel = WINDOW_HEIGHT - 1;

        t_texture *texture = NULL;
        float wall_hit = 0;
        int flip_x = 0;
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

        if (!texture || !texture->data)
            return -1;

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