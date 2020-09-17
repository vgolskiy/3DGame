/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:19:53 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 11:08:41 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_texture_paths(t_info *info)
{
	if (info->north_texture_path)
		info->north_texture_path = ft_free(info->north_texture_path);
	if (info->south_texture_path)
		info->south_texture_path = ft_free(info->south_texture_path);
	if (info->west_texture_path)
		info->west_texture_path = ft_free(info->west_texture_path);
	if (info->east_texture_path)
		info->east_texture_path = ft_free(info->east_texture_path);
	if (info->sprite_texture_path)
		info->sprite_texture_path = ft_free(info->sprite_texture_path);
}

int		free_cub(t_info *info)
{
	if (info->img.img)
		mlx_destroy_image(info->mlx, info->img.img);
	if (info->sprite)
		info->sprite = ft_free(info->sprite);
	if (info->buf)
		info->buf = ft_free_2d_int(info->buf, info->height);
	if (info->z_buffer)
		info->z_buffer = ft_free(info->z_buffer);
	if (info->texture)
		info->texture = ft_free_2d_int(info->texture, 5);
	if (info->map)
		info->map = ft_free_2d(info->map);
	if (info->map_2d)
		info->map_2d = ft_free_2d(info->map_2d);
	if ((info->mlx) && (info->win))
		mlx_destroy_window(info->mlx, info->win);
	free_texture_paths(info);
	ft_exit(0);
	return (0);
}
