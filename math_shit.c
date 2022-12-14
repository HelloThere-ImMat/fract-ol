/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:48:34 by mdorr             #+#    #+#             */
/*   Updated: 2022/12/31 16:16:54 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//Func that will translate pixel position into a 2d plan with (0;0) in the center

float get_syst_pos(int x, int axis, t_data *data)
{
	float c;

	if (axis == 0)
		c = (float)x * (data->Xmax - data->Xmin) / (float)(WINDOW_WIDTH) + data->Xmin;
	if (axis == 1)
		c = ((float)x * (data->Ymax - data->Ymin) / (float)(WINDOW_HEIGHT) + data->Ymin);
	return (c);
}

//This function calculates the new mathematic borders of our 2d visualisationaa

float get_new_border(float x, float y, int type, t_data *data)
{
	if (type == ZOOM_IN_XMIN)
		 return (data->Xmin - (ZOOM_RATIO * (data->Xmin - x)));
	if (type == ZOOM_IN_XMAX)
		return (data->Xmax - (ZOOM_RATIO * (data->Xmax - x)));
	if (type == ZOOM_IN_YMIN)
		return (data->Ymin - (ZOOM_RATIO * (data->Ymin - y)));
	if (type == ZOOM_IN_YMAX)
		return (data->Ymax - (ZOOM_RATIO * (data->Ymax - y)));
	if (type == ZOOM_OUT_XMIN)
		 return (data->Xmin + (ZOOM_RATIO * (data->Xmin - x)));
	if (type == ZOOM_OUT_XMAX)
		return (data->Xmax + (ZOOM_RATIO * (data->Xmax - x)));
	if (type == ZOOM_OUT_YMIN)
		return (data->Ymin + (ZOOM_RATIO * (data->Ymin - y)));
	if (type == ZOOM_OUT_YMAX)
		return (data->Ymax + (ZOOM_RATIO * (data->Ymax - y)));
	else
		return (0);
}


int color_main(int i, int j, t_data *data)
{
	float x;
	float y;
	int color;

	x = get_syst_pos(i, 0, data);
	y = get_syst_pos(j, 1, data);
	if (data->fractal == 1)
		color = color_julia(x, y, data->Cx, data->Cy);
	if (data->fractal == 2)
		color = color_mandelbrot(x, y);
	return (color);
}

//Func that checks if the complex number belong to the mandelbrot set

int	color_mandelbrot(float x, float y)
{
	int	iteration;
	int color;
	double	xOld;
	double	yOld;
	double	xNew;
	double	yNew;

	xNew = 0;
	yNew = 0;
	iteration = 0;
	while ((xNew * xNew + yNew * yNew) < 4 && iteration < MAX_ITERATION)
	{
		xOld = xNew;
		yOld = yNew;
		xNew = xOld * xOld - yOld * yOld + x;
		yNew = 2 * xOld * yOld + y;
		iteration++;
	}
	color = color_palette(iteration);
	return (color);

}

int color_julia(float x, float y, float cx, float cy)
{
	int	iteration;
	int color;
	double	xOld;
	double	yOld;
	double	xNew;
	double	yNew;

	xNew = x;
	yNew = y;
	iteration = 0;
	while ((xNew * xNew + yNew * yNew) < 4 && iteration < MAX_ITERATION)
	{
		xOld = xNew;
		yOld = yNew;
		xNew = xOld * xOld - yOld * yOld + cx;
		yNew = 2 * xOld * yOld + cy;
		iteration++;
	}
	color = color_palette(iteration);
	return (color);
}

int color_palette(int iteration)
{
	if (iteration < MAX_ITERATION / 4)
		return (BLACK_BLUE);
	if (iteration < MAX_ITERATION / 3)
		return (DARK_BLUE);
	if (iteration < MAX_ITERATION / 2)
		return (BLUE);
	if (iteration < MAX_ITERATION - 20)
		return (GREEN);
	if (iteration < MAX_ITERATION)
		return (WHITISH);
	else
		return (BLACK);
}

//int main(void)
//{
//	printf("%d\n", color_mandelbrot(0, 0));
//	return (0);
//}
