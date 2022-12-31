/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:23:08 by mdorr             #+#    #+#             */
/*   Updated: 2022/12/29 00:02:44 by mdorr            ###   ########.fr       */
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

float	ft_atof(char* nptr)
{
	int	a;
	int	e;
	int	sign;
	float	res;

	a = 0;
	e = 0;
	sign = 1;
	res = 0;
	while (nptr[a])
	{
		while ((nptr[a] > 8 && nptr[a] < 14) || nptr[a] == 32)
			a++;
		if (nptr[a] == '-' || nptr[a] == '+')
		{
			if (nptr[a] == 45)
				sign = sign * -1;
			a++;
		}
		while (nptr[a] >= 48 && nptr[a] <= 57 && nptr[a] != 46)
		{
			res = res * 10 + nptr[a] - '0';
			a++;
		}
		a++;
		while (nptr[a] >= 48 && nptr[a] <= 57)
		{
			res = res * 10 + nptr[a] - '0';
			a++;
			e++;
		}
		while (e > 0)
		{
			res *= 0.1;
			e--;
		}
		return (res);
	}
	//to be checked
	return (res);
}

int	check_arg(int argc, char **argv, t_data *data)
{
	char *mandel;
	char *julia;

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
			data->Cx  = -0.7;
			data->Cy = 0.27015;
		}
		if (argc == 4)
		 {
		 	data->Cx = ft_atof(argv[2]);
		 	data->Cy = ft_atof(argv[3]);
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
		printf("Invalid number of arguments, please only write the fractal name\n");
	if (error_type == 2)
		printf("Invalid fractal name \nOptions are : mandelbrot, julia\n");
}
