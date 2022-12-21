/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:20:35 by mdorr             #+#    #+#             */
/*   Updated: 2022/12/21 14:52:58 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void get_syst(t_data *data)
{
	data->Xmin = -3;
	data->Xmax = 3;
	data->Ymin = -3;
	data->Ymax = 3;
}

int render_set(t_img *img, t_data *data)
{
	int i;
	int j;

	i = 0;
	get_syst(data);
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while  (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j, i, color_main(i, j, data));
			j++;
		}
		i++;
	}
	return (0);
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (MLX_ERROR);
	//render_background(&data->img, WHITE_PIXEL);
	//render_rect(&data->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT -100, 100, 100, GREEN_PIXEL});
	//render_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL});
	render_set(&data->img, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}

int handle_key_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int	 handle_mouse_input(int mousesym, t_data *data)
{
	if (mousesym == 5)
	{
		data->Xmax =-1;
		data->Xmin =-1;
		data->Ymax =-1;
		data->Ymin =-1;
	}
	if (mousesym == 4)
	{
		data->Xmax =+1;
		data->Xmin =+1;
		data->Ymax =+1;
		data->Ymin =+1;
	}
	//printf("%d", mousesym);
	return (0);
}


int main ()
{
	t_data	data;


	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);

	//mlx_mouse_hook(data.win_ptr, &handle_mouse_input, &data);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_key_input, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_display(data.mlx_ptr);

	free(data.mlx_ptr);
}
