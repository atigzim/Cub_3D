/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:08:24 by atigzim           #+#    #+#             */
/*   Updated: 2025/12/10 22:13:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub_3d.h"

int	key_press(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == ESC)
	{
		if(data)
			free_data(data);
		exit(0);
	}
	else
		move_player(data, keycode);
	return (0);
}

int	sed(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data)
		free_data(data);
	exit(0);
	return (0);
}

int	game_loop(t_data *data)
{
	draw_all(data);
	if (data && data->mlx && data->window && data->buffer.img_ptr)
		mlx_put_image_to_window(data->mlx, data->window, data->buffer.img_ptr,
			0, 0);
	return (0);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	if (ac != 2)
	{
		printf("Usage: %s <map.cub>\n", av[0]);
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_bzero(data, sizeof(t_data));
	pars_main(data, av[1]);
	free_data(data);
	return (0);
}
