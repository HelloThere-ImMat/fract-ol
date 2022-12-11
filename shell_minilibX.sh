# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    shell_minilibX.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdorr <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/11 14:04:01 by mdorr             #+#    #+#              #
#    Updated: 2022/12/11 14:09:03 by mdorr            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

gcc fract-ol.c minilibx_linux/libmxl.a -L ./minilibx-linux -l mlx -lXext -lX11

clang fract-ol minilibx-linus/libmlx.a -L ./minilibx-linux -l mlx -lXext -lX11
