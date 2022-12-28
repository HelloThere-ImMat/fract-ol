/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:00:02 by mdorr             #+#    #+#             */
/*   Updated: 2022/12/28 16:15:25 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//dans le cadre de fractol, j'ai besoin de traduire un char* en float

#include <stdio.h>

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
}

int main(int argc, char** argv)
{
	int i;
	int i2;

	i = argc;
	i2 = 1;
	while (i > 0)
	{
		printf("%0.5f", ft_atof(argv[i2]));
		i2++;
		i--;
	}
	return (0);
}



//atoi for inspiration

int	ft_atoi(const char *nptr)
{
	int	a;
	int	res;
	int	sign;

	a = 0;
	sign = 1;
	res = 0;
	while (nptr[a] != '\0')
	{
		while ((nptr[a] > 8 && nptr[a] < 14) || nptr[a] == 32)
			a++;
		if (nptr[a] == '-' || nptr[a] == '+')
		{
			if (nptr[a] == 45)
				sign = sign * -1;
			a++;
		}
		while (nptr[a] >= 48 && nptr[a] <= 57)
		{
			res = res * 10 + nptr[a] - '0';
			a++;
		}
		return (res * sign);
	}
	return (0);
}
