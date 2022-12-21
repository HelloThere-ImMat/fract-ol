/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:48:34 by mdorr             #+#    #+#             */
/*   Updated: 2022/12/21 14:39:36 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int color_palette(int iteration)
{
	int i;

	i = 1;
	if (iteration < MAX_ITERATION / 4)
		return (0x000000);
	if (iteration < MAX_ITERATION / 2)
		return (0x0000F0);
	if (iteration < MAX_ITERATION)
		return (0xFFEFFF);
	//white
	else
		return (0x00000E);
}

//Func that will translate pixel position into a 2d plan with (0;0) in the center

int color_main(int i, int j, t_data *data)
{
	float cx;
	float cy;
	int color;

	cx = (float)j * (data->Xmax - data->Xmin) / (float)(WINDOW_WIDTH) + data->Xmin;
	cy = (float)i * (data->Ymax - data->Ymin) / (float)(WINDOW_HEIGHT) + data->Ymin;
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

//int main(void)
//{
//	printf("%d\n", color_mandelbrot(0, 0));
//	return (0);
//}
