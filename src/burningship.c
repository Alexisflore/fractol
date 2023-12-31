/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfloren <alfloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:09:17 by alfloren          #+#    #+#             */
/*   Updated: 2023/12/19 19:22:13 by alfloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	burningship_init(t_fractol *data)
{
	data->it_max = 50;
	data->zoom = 200;
	data->x1 = -2.2;
	data->y1 = -2.5;
	data->color = 265;
	data->julia_mouse = 0;
	data->y_max = 0;
	data->it = 0;
	data->show_text = 0;
	data->endian = 0;
	data->sl = 0;
	data->bpp = 0;
	data->c_r = data->x / data->zoom + data->x1;
	data->c_i = data->y / data->zoom + data->y1;
}

void	burningship_calc(t_fractol *data)
{
	data->c_r = data->x / data->zoom + data->x1;
	data->c_i = data->y / data->zoom + data->y1;
	data->z_r = 0;
	data->z_i = 0;
	data->it = 0;
	while (data->z_r * data->z_r + data->z_i * data->z_i < 4
		&& data->it < data->it_max)
	{
		data->tmp = data->z_r * data->z_r - data->z_i * data->z_i + data->c_r;
		data->z_i = fabs(2 * data->z_r * data->z_i) + data->c_i;
		data->z_r = data->tmp;
		data->it++;
	}
	if (data->it == data->it_max)
		put_pxl_to_img(data, data->x, data->y, 0x000000);
	else
		put_pxl_to_img(data, data->x, data->y, (data->color * data->it));
}

void	*burningship(void *tab)
{
	int			tmp;
	t_fractol	*data;

	data = (t_fractol *)tab;
	data->x = 0;
	tmp = data->y;
	while (data->x < WIDTH)
	{
		data->y = tmp;
		while (data->y < data->y_max)
		{
			burningship_calc(data);
			data->y++;
		}
		data->x++;
	}
	return (tab);
}

void	burningship_line(t_fractol *data)
{
	t_fractol	tab[MAX_NUMBER];
	int			i;

	i = 0;
	while (i < MAX_NUMBER)
	{
		ft_memcpy((void *)&tab[i], (void *)data, sizeof(t_fractol));
		tab[i].y = N_WIDTH * i;
		tab[i].y_max = N_WIDTH * (i + 1);
		burningship(&tab[i]);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
