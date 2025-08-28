#include "../include/cub_3d.h"

int	key_press(int keycode)
{
	if (keycode == ESC)
		{
			//free_all
			exit(0);
		}
	// if (keycode == D || keycode == 65363)
	// 	mov_right(mlx);
	// else if (keycode == W || keycode == 65362)
	// 	mov_up(mlx);
	// else if (keycode == A || keycode == 65361)
	// 	mov_left(mlx);
	// else if (keycode == S || keycode == 65364)
	// 	mov_down(mlx);
	return (0);
}
void	ft_raycastung(t_data *data)
{
	data->mlx = mlx_init();
	if(!data->mlx)
	{
		//free_all;
		return ;
	}
	data->window = mlx_new_window(data->mlx, data->map_width *MAX_WIDTH ,
			 data->map_height * MAX_HEIGHT , "Cub_3D");
	mlx_loop(data->mlx);
	mlx_hook(data->mlx, 2, 1L << 0, &key_press, &data);
}
