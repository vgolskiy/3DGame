/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 09:10:27 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 11:08:41 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	raycasting(t_info *info)
{
	int	x;

	x = 0;
	cast_floor_ceiling(info);
	while (x < info->width)
	{
		init_ray(info, &info->player, &info->ray, x);
		calculate_step_direction(&info->player, &info->ray);
		perform_dda(info, &info->ray);
		calculate_wall_distance(&info->player, &info->ray);
		calculate_wall_height(info, &info->ray);
		get_wall_texture(&info->player, &info->ray);
		get_wall_color(info, &info->ray, x);
		draw_2d_map(info);
		put_2d_player(info, color_pack(0, 153, 51, 255));
		info->z_buffer[x] = info->ray.perp_wall_dist;
		x++;
	}
}

void	sprite_raycasting(t_info *info, t_player *player)
{
	int	i;
	int	stripe;

	sort_sprite(info, player);
	i = 0;
	while (i < info->num_sprite)
	{
		translate_sprite(info, player, &info->s_ray, i);
		calculate_sprite_height(info, &info->s_ray);
		calculate_sprite_width(info, &info->s_ray);
		stripe = info->s_ray.draw_start_x;
		while (stripe < info->s_ray.draw_end_x)
		{
			get_sprite_color(info, &info->s_ray, stripe);
			stripe++;
		}
		i++;
	}
}

int		main_loop(t_info *info)
{
	raycasting(info);
	sprite_raycasting(info, &info->player);
	draw(info);
	return (0);
}
