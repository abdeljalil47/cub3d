#include "../header/cub3d.h"

long	get_time()
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		return ft_putstr_fd("ERROR\ngettimeofday failed!\n", 2), -1;
	return (long)((tv.tv_sec * 1000000) + tv.tv_usec);
}

char *ft_return_file(int i)
{
	char	*rel_path;
	char	*full_id;
	char	*path;
	char	*id;

	id = ft_itoa(i);
	if (!id)
		return NULL;
	rel_path = "texture/";
	full_id = ft_strjoin(id, ".xpm");
	if (!full_id)
		return free(id), NULL;
	path = ft_strjoin(rel_path, full_id);
	if (!path)
		return free(full_id), free(id), NULL;
	free(full_id);
	free(id);
	return path;
}

int	get_path_frame(t_table **param)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (*param)->data;
	while (i < 44)
	{
		data->frames[i] = ft_return_file(i);
		if (!data->frames[i])
			return 0;//TODO: free_frames();
		i++;
	}
	i = 0;
	while (i < 44)
	{
		data->mlx_frame[i] = mlx_xpm_file_to_image((*param)->mlx,
													data->frames[i],
													&data->width,
													&data->height
												);
		if (!data->mlx_frame[i])
			return 0;
		i++;
	}
	return 1;
}

int	player_effect(void *param)
{
	t_table *table;
	long	time;
	
	time = get_time();
	if (time < 0)
		return 0;
	table = (t_table *)param;
	if (time - table->data->current_time >= 100000)
	{
		mlx_clear_window(table->mlx, table->mlx_win);
		// printf("frame:%s\n", table->data->frames[table->data->frame_id]);
		if (table->data->mlx_frame[table->data->frame_id])
        {
            mlx_put_image_to_window(table->mlx,
									table->mlx_win,
									table->data->mlx_frame[table->data->frame_id],
									table->player_coor->position_y * 64,
									table->player_coor->position_x * 64);
        }
        table->data->frame_id = (table->data->frame_id + 1) % 44;
		table->data->current_time = time;
	}
	put_texture(table);
	return 1;
}
