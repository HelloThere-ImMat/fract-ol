/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:48:34 by mdorr             #+#    #+#             */
/*   Updated: 2022/12/26 13:04:39 by mdorr            ###   ########.fr       */
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
		c = -((float)x * (data->Ymax - data->Ymin) / (float)(WINDOW_HEIGHT) + data->Ymin);
	return (c);
}

//This function calculates the new mathematic borders of our 2d visualisationaa

float get_new_border(float x, float y, int type, t_data *data)
{

//why the fuck am i never using y ?

	if (type == 1)
		 return (data->Xmax - 0.25 * (data->Xmax - x));
	if (type == 2)
		return (data->Xmin - 0.25 * (data->Xmin - x));
	if (type == 3)
		return (data->Ymax - 0.25 * (data->Ymax - x));
	if (type == 4)
		return (data->Ymin - 0.25 * (data->Ymin - x));
	if (type == 5)
		 return (data->Xmax + 0.25 * (data->Xmax - x));
	if (type == 6)
		return (data->Xmin + 0.25 * (data->Xmin - x));
	if (type == 7)
		return (data->Ymax + 0.25 * (data->Ymax - x));
	if (type == 8)
		return (data->Ymin + 0.25 * (data->Ymin - x));
	else
		return (0);
}


int color_main(int i, int j, t_data *data)
{
	float cx;
	float cy;
	int color;

	cx = get_syst_pos(i, 0, data);
	cy = get_syst_pos(j, 1, data);
	color = color_mandelbrot(cx, cy);
	return (color);
}

//Func that checks if the complex number belong to the mandelbrot set

int	color_mandelbrot(float x, float y)
{
	int	iteration;
	int color;
	float	xtmp;
	float	ytmp;
	float	xn;
	float	yn;

	xn = 0;
	yn = 0;
	iteration = 0;
	while ((xn * xn + yn * yn) < 4 && iteration < MAX_ITERATION)
	{
		xtmp = xn;
		ytmp = yn;
		xn = xtmp * xtmp - ytmp * ytmp + x;
		yn = 2 * xtmp * ytmp + y;
		iteration++;
	}
	color = color_palette(iteration);
	return (color);

}

int color_palette(int iteration)
{
	// if (iteration < MAX_ITERATION / 4)
	// 	return (DARK_BLUE);
	// if (iteration < MAX_ITERATION / 3)
	// 	return (ORANGE);
	// if (iteration < MAX_ITERATION / 2)
	// 	return (BLUE);
	// if (iteration < MAX_ITERATION - 20)
	// 	return (GREEN);
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
