/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:23:08 by mdorr             #+#    #+#             */
/*   Updated: 2022/12/28 16:22:44 by mdorr            ###   ########.fr       */
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

int	check_arg(int argc, char **argv, t_data *data)
{
	char *mandel;
	char *julia;

	if (argc != 2 || argc != 4)
	{
		print_error(1);
		return (0);
	}
	mandel = "mandelbrot";
	julia = "julia";
	if (ft_strcmp(argv[1], julia) == 0)
	{
		data->fractal = 1;
		data->Cx  = -0.7;
		data->Cy = 0.27015;
		//if (argc == 4)
		// {
		// 	data->Cx = ft_atoi(argv[2]);
		// 	data->Cy = ft_atoi(argv[3]);
		// }
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
		printf("Invalid number of arguments, please only write the fractal name\n");
	if (error_type == 2)
		printf("Invalid fractal name \nOptions are : mandelbrot, julia\n");
}
