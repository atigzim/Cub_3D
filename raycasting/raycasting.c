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
	/*
	010010010010111
	010010010010111
	010010010010111
	010010010010111
	010010010010111
	010010010010111
	010010010010111
	*/
}

int	sed(t_data *mlx)
{
	//feer_all
	(void)mlx;
	exit(0);
	return (0);
}

void init_buffer(t_data *mlx)
{
	mlx->buffer = malloc(sizeof(t_image));
	if (!mlx->buffer)
	{
		// free_all
		perror("alloction not valid");
	}
	mlx->buffer->img_ptr = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->buffer->width =  WIN_WIDTH;
	mlx->buffer->height =  WIN_HEIGHT;
	mlx->buffer->pixel_data = mlx_get_data_addr(
        mlx->buffer->img_ptr, &mlx->buffer->bpp,
        &mlx->buffer->line_size, &mlx->buffer->endian);
}

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char *dst;

    dst = img->pixel_data + (y * img->line_size + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}
void draw_block(t_image *img, int x, int y, int cool)
{
	int i;
	int j ;

	j = x;
	while (j < x + TILE_SIZE)
	{
		i = y;
		while (i < y + TILE_SIZE)
		{
			my_mlx_pixel_put(img, j, i, cool);
			i++;
		}
		j++;
	}
}

void draw_background(t_data *data)
{
	t_image *img;
	int y;
	int i;

	i = 0;
	img = data->buffer;
	while(data->map[i])
	{
		y = 0;
		while(data->map[i][y])
		{
			if(data->map[i][y] == '1')
				draw_block(img, y * TILE_SIZE, i * TILE_SIZE, 0xFF0000);
			else if(data->map[i][y] != '0' && data->map[i][y] != '1')
				draw_block(img, y * TILE_SIZE, i * TILE_SIZE, 0x00FF00);
			y++;
		}
		i++;
	}
	
}

void init_player(t_data *data)
{
	t_player *player;
	
	player = data->player;
	player = malloc(sizeof(t_player));
	ft_bzero(player, sizeof(t_player));
	player->move_speed = 3;
	player->rotation_speed = 0.09;
	if (data->player_dir == 'N')
		player->angle = -M_PI / 2;
	else if (data->player_dir == 'S')
		player->angle = M_PI / 2;
	else if (data->player_dir == 'W')
		player->angle = M_PI;
	else
		player->angle = 0;
}


int game_loop(t_data *data)
{
    draw_background(data);
    mlx_put_image_to_window(data->mlx, data->window, data->buffer->img_ptr, 0, 0);
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
	data->window = mlx_new_window(data->mlx, WIN_WIDTH ,
			 WIN_HEIGHT , "Cub_3D");
	init_buffer(data);
	init_player(data);
	mlx_hook(data->window, 2, 1L << 0, key_press, data);
	mlx_hook(data->window, 17, 0, sed, data);
	mlx_loop_hook(data->mlx, game_loop, (t_data *) data);
	mlx_loop(data->mlx);
}
