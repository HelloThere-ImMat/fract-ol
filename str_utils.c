/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:03:21 by mdorr             #+#    #+#             */
/*   Updated: 2023/01/26 15:43:00 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_sign(char *nptr, int *a)
{
	int	sign;

	sign = 1;
	while ((nptr[*a] > 8 && nptr[*a] < 14) || nptr[*a] == 32)
			(*a)++;
	if (nptr[*a] == '-' || nptr[*a] == '+')
	{
		if (nptr[*a] == 45)
			sign = sign * -1;
		(*a)++;
	}
	return (sign);
}

float	ft_atof(char *nptr)
{
	int		a;
	int		e;
	int		sign;
	float	res;

	a = 0;
	e = 0;
	res = 0;
	while (nptr[a])
	{
		sign = get_sign(nptr, &a);
		while (nptr[a] >= 48 && nptr[a] <= 57 && nptr[a] != 46)
			res = res * 10 + nptr[a++] - '0';
		a++;
		while (nptr[a] >= 48 && nptr[a] <= 57)
		{
			res = res * 10 + nptr[a] - '0';
			a++;
			e++;
		}
		while (e-- > 0)
			res *= 0.1;
	}
	return (sign * res);
}

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
