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

// void draw_background(t_data *data)
// {
// 	t_image *img;
// 	int y;
// 	int i;

// 	i = 0;
// 	img = data->buffer;
// 	while(data->map[i])
// 	{
// 		y = 0;
// 		while(data->map[i][y])
// 		{
// 			if(data->map[i][y] == '1')
// 				draw_block(img, y * TILE_SIZE, i * TILE_SIZE, 0xFF0000);
// 			else if(data->map[i][y] != '0' && data->map[i][y] != '1')
// 				draw_block(img, y * TILE_SIZE, i * TILE_SIZE, 0x00FF00);
// 			if()
// 			y++;
// 		}
// 		i++;
// 	}
	
// }

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
#include <math.h>

// small helper: clamp pixel x/y inside buffer bounds
static inline bool in_screen(int x, int y)
{
    return (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT);
}

// draw a vertical line on the buffer (x column), from y0 (inclusive) to y1 (exclusive)
void draw_vertical_line(t_data *data, int x, int y0, int y1, int color)
{
    if (x < 0 || x >= WIN_WIDTH) return;
    if (y0 < 0) y0 = 0;
    if (y1 > WIN_HEIGHT) y1 = WIN_HEIGHT;
    for (int y = y0; y < y1; ++y)
        my_mlx_pixel_put(data->buffer, x, y, color);
}

// Cast a single ray for screen column 'col' using DDA and draw the vertical wall slice.
void cast_single_ray(t_data *data, int col)
{
    t_player *p = data->player;
    // Player position in map grid units (tile coordinates)
    double posX = p->x / (double)TILE_SIZE;
    double posY = p->y / (double)TILE_SIZE;

    // Field of view: typical value 60 degrees
    const double FOV = M_PI / 3.0; // 60 degrees

    // Compute ray angle for this screen column
    double cameraX = 2.0 * col / (double)WIN_WIDTH - 1.0; // -1 .. 1
    double rayAngle = p->angle + atan(cameraX * tan(FOV / 2.0));
    // Alternative (linear) formula also works: rayAngle = p->angle - FOV/2 + col * FOV / WIN_WIDTH;

    // Ray direction
    double rayDirX = cos(rayAngle);
    double rayDirY = sin(rayAngle);

    // Current map square where the ray is
    int mapX = (int)floor(posX);
    int mapY = (int)floor(posY);

    // length of ray from one x or y-side to next x or y-side
    double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

    // step direction and initial sideDist
    int stepX, stepY;
    double sideDistX, sideDistY;

    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    // perform DDA
    int hit = 0;
    int side = 0; // 0 => hit on an X side (vertical wall), 1 => Y side (horizontal wall)
    while (!hit)
    {
        // jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        // check if ray has hit a wall (ensure map indexes are in bounds)
        if (mapY >= 0 && mapY < data->map_height && mapX >= 0 && mapX < data->map_width)
        {
            if (data->map[mapY][mapX] == '1')
                hit = 1;
        }
        else
        {
            // out of bounds => treat as wall
            hit = 1;
        }
    }

    // Calculate distance to the point of impact (perpendicular distance)
    double perpWallDist;
    if (side == 0)
        perpWallDist = (mapX - posX + (1 - stepX) / 2.0) / rayDirX;
    else
        perpWallDist = (mapY - posY + (1 - stepY) / 2.0) / rayDirY;

    if (perpWallDist <= 0) perpWallDist = 0.0001; // safety

    // Calculate height of line to draw on screen
    int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

    // Calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
    int drawEnd   = lineHeight / 2 + WIN_HEIGHT / 2;

    // simple shading: darker color when hit side==1
    int color = 0xFFFFFF; // white
    if (side == 1) color = 0xAAAAAA; // slightly darker

    // Optionally choose wall color based on which side (N,S,E,W)
    // You can read which face by looking at rayDir and step sign if you want textured mapping.

    // Draw vertical stripe
    // Draw ceiling
    for (int y = 0; y < drawStart; ++y)
        my_mlx_pixel_put(data->buffer, col, y, data->ceiling_color);

    // Draw wall
    draw_vertical_line(data, col, drawStart, drawEnd, color);

    // Draw floor
    for (int y = drawEnd; y < WIN_HEIGHT; ++y)
        my_mlx_pixel_put(data->buffer, col, y, data->floor_color);
}

// void cast_ray(t_data *data)
// {
// 	t_ray *ray;

// 	ray = data->ray;

// 	ray->ray_angle = data->player->angle - (FOV - 2) + (i * FOV / WIN_WIDTH);
// 	ray->ray_dx = cos(ray_angle); 
// 	ray->ray_dy = sin(ray_angle); 
// }

// int game_loop(t_data *data)
// {
// 	cast_ray(data);
//     draw_background(data);
//     mlx_put_image_to_window(data->mlx, data->window, data->buffer->img_ptr, 0, 0);
//     return (0);
// }
int game_loop(t_data *data)
{
    // Ensure floor and ceiling colors are set in data->floor_color / data->ceiling_color
    // Optional: clear buffer first (not strictly necessary if we fill every pixel)
    for (int x = 0; x < WIN_WIDTH; ++x)
        cast_single_ray(data, x);

    mlx_put_image_to_window(data->mlx, data->window, data->buffer->img_ptr, 0, 0);
    return 0;
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
