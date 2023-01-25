/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:23:08 by mdorr             #+#    #+#             */
/*   Updated: 2023/01/25 16:23:57 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	e;

	e = 0;
	while (s1[e] != '\0' && s2[e] != '\0')
	{
		if (s1[e] != s2[e])
		{
			return (s1[e] - s2[e]);
		}
		e++;
	}
	return (s1[e] - s2[e]);
}

//PENSER A RAJOUTER LE CHECK DES ARG DE JULIA (FORMAT FLOAT)

int	check_arg(int argc, char **argv, t_data *data)
{
	char	*mandel;
	char	*julia;

	if (argc != 2 && argc != 4)
	{
		print_error(1);
		return (0);
	}
	mandel = "mandelbrot";
	julia = "julia";
	if (ft_strcmp(argv[1], julia) == 0)
	{
		data->fractal = 1;
		if (argc == 2)
		{
			data->cx = -0.7;
			data->cy = 0.27015;
		}
		if (argc == 4)
		{
			data->cx = ft_atof(argv[2]);
			data->cy = ft_atof(argv[3]);
		}
		return (1);
	}
	if (ft_strcmp(argv[1], mandel) == 0)
	{
		data->fractal = 2;
		return (1);
	}
	print_error(2);
	return (0);
}

void	print_error(int error_type)
{
	if (error_type == 1)
		write(1, "Invalid number of arguments\n", 28);
	if (error_type == 2)
		write(1, "Invalid fractal name\nOptions are : mandelbrot, julia\n", 53);
}

float	get_syst_pos(int x, int axis, t_data *data)
{
	double	c;

	if (axis == 0)
		c = (float)x * (data->xmax - data->xmin)
			/ (float)(W_WIDTH) + data->xmin;
	if (axis == 1)
		c = ((float)x * (data->ymax - data->ymin)
				/ (float)(W_HEIGHT) + data->ymin);
	return (c);
}
