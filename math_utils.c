/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:48:34 by mdorr             #+#    #+#             */
/*   Updated: 2023/01/28 13:13:50 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//This function calculates the new mathematic borders of our 2d visualisation

float	get_new_border(float x, float y, int type, t_data *data)
{
	if (type == ZOOM_IN_XMIN)
		return (data->xmin - (ZOOM_RATIO * (data->xmin - x)));
	if (type == ZOOM_IN_XMAX)
		return (data->xmax - (ZOOM_RATIO * (data->xmax - x)));
	if (type == ZOOM_IN_YMIN)
		return (data->ymin - (ZOOM_RATIO * (data->ymin - y)));
	if (type == ZOOM_IN_YMAX)
		return (data->ymax - (ZOOM_RATIO * (data->ymax - y)));
	if (type == ZOOM_OUT_XMIN)
		return (data->xmin + (ZOOM_RATIO * (data->xmin - x)));
	if (type == ZOOM_OUT_XMAX)
		return (data->xmax + (ZOOM_RATIO * (data->xmax - x)));
	if (type == ZOOM_OUT_YMIN)
		return (data->ymin + (ZOOM_RATIO * (data->ymin - y)));
	if (type == ZOOM_OUT_YMAX)
		return (data->ymax + (ZOOM_RATIO * (data->ymax - y)));
	else
		return (0);
}

int	color_main(int i, int j, t_data *data)
{
	double	x;
	double	y;
	int		color;

	x = get_syst_pos(i, 0, data);
	y = get_syst_pos(j, 1, data);
	if (data->fractal == 1)
		color = color_julia(x, y, data);
	if (data->fractal == 2)
		color = color_mandelbrot(x, y, data);
	return (color);
}

//Func that checks if the complex number belong to the mandelbrot set

int	color_mandelbrot(float x, float y, t_data *d)
{
	int		iteration;
	int		color;

	d->xnew = 0;
	d->ynew = 0;
	iteration = 0;
	while ((d->xnew * d->xnew + d->ynew * d->ynew) < 4
		&& iteration < MAX_ITERATION)
	{
		d->xold = d->xnew;
		d->yold = d->ynew;
		d->xnew = d->xold * d->xold - d->yold * d->yold + x;
		d->ynew = 2 * d->xold * d->yold + y;
		iteration++;
	}
	color = color_palette(iteration, d);
	return (color);
}

int	color_julia(float x, float y, t_data *d)
{
	int	iteration;
	int	color;

	d->xnew = x;
	d->ynew = y;
	iteration = 0;
	while ((d->xnew * d->xnew + d->ynew * d->ynew) < 4
		&& iteration < MAX_ITERATION)
	{
		d->xold = d->xnew;
		d->yold = d->ynew;
		d->xnew = d->xold * d->xold - d->yold * d->yold + d->cx;
		d->ynew = 2 * d->xold * d->yold + d->cy;
		iteration++;
	}
	color = color_palette(iteration, d);
	return (color);
}

int	color_palette(int iteration, t_data *data)
{
	if (data->color > 3)
		data->color = 1;
	if (iteration < MAX_ITERATION / 10)
		return (BLACK_BLUE);
	else if (iteration >= MAX_ITERATION)
		return (BLACK);
	else
	{
		if (data->color == 1)
			return (iteration * 0x08ED55);
		if (data->color == 2)
			return (iteration * 0x654321);
		if (data->color == 3)
			return (iteration * 0x5150A);
	}
	return (BLACK);
}
