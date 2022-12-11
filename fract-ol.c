/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:20:35 by mdorr             #+#    #+#             */
/*   Updated: 2022/12/11 17:30:07 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>

#include "minilibx-linux/mlx.h"
#include "libft/libft.h"

typedef struct s_data
{
	void *mlx_ptr;
	void *win_ptr;
}	t_data;

int handle_no_event(void *data)
{
	return (0);
}

int handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}


int main ()
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (0);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 500, 400, "My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (0);
	}


	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_key_hook(data.win_ptr, &handle_input, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_display(data.mlx_ptr);

	free(data.mlx_ptr);
}