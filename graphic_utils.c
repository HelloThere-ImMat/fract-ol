/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 02:48:43 by mdorr             #+#    #+#             */
/*   Updated: 2023/02/01 18:56:25 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	image_init(t_data *data)
{
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &(*data).img.bpp,
			&(*data).img.line_len, &(*data).img.endian);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	render_set(t_img *img, t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < W_HEIGHT)
	{
		i = 0;
		while (i < W_WIDTH)
		{
			img_pix_put(img, i, j, color_main(i, j, data));
			i++;
		}
		j++;
	}
	return (0);
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (MLX_ERROR);
	render_set(&data->img, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	return (0);
}

int	quit_window(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	data->win_ptr = NULL;
	free(data->mlx_ptr);
	write(1, "DESTROYED\n", 10);
	exit(EXIT_SUCCESS);
}
