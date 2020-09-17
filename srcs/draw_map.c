/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 09:08:40 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 11:08:41 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		color_pack(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_2d_map(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->map_height)
	{
		j = -1;
		while (++j < info->map_width)
		{
			if (info->map_2d[j][i] == '1')
				put_square(info, j, i, color_pack(0, 255, 153, 51));
			else if (info->map_2d[j][i] == '2')
				put_square(info, j, i, color_pack(0, 255, 0, 0));
		}
	}
}

void	put_square(t_info *info, int i, int j, int color)
{
	int	dx;
	int	dy;
	int	size;
	int	pos_x;
	int	pos_y;

	dx = 0;
	size = (info->map_2d[i][j] == '1') ? MAP_WALL_2D : SPRITE_2D;
	pos_x = (info->map_2d[i][j] == '1') ? i * MAP_WALL_2D
		: (i + 0.5f) * MAP_WALL_2D;
	pos_y = (info->map_2d[i][j] == '1') ? j * MAP_WALL_2D
		: (j + 0.5f) * MAP_WALL_2D;
	while ((dx < size) && ((pos_x + dx) < info->width))
	{
		dy = 0;
		while ((dy < size) && ((pos_y + dy) < info->height))
			info->buf[pos_x + dx][pos_y + dy++] = color;
		dx++;
	}
}

void	put_2d_player(t_info *info, int color)
{
	int	dx;
	int	dy;
	int	pos_x;
	int	pos_y;
	int	size;

	dx = 0;
	size = PLAYER_2D;
	pos_x = info->player.x * MAP_WALL_2D - size / 2;
	pos_y = info->player.y * MAP_WALL_2D - size / 2;
	while ((dx < size) && ((pos_x + dx) < info->width))
	{
		dy = 0;
		while ((dy < size) && ((pos_y + dy) < info->height))
			info->buf[pos_x + dx][pos_y + dy++] = color;
		dx++;
	}
}
