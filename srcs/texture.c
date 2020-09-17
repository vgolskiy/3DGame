/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 19:24:10 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 11:08:41 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cast_floor_ceiling(t_info *info)
{
	int	y;
	int	x;

	y = 0;
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			if (y > info->height / 2)
				info->buf[y][x] = info->floor_color;
			else
				info->buf[y][x] = info->ceiling_color;
			x++;
		}
		y++;
	}
}

int		load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int		x;
	int		y;

	if (!(img->img = mlx_xpm_file_to_image(info->mlx, path,
									&img->width, &img->height)))
		return (exit_error(info, 17));
	if (!(img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
									&img->size_l, &img->endian)))
		return (exit_error(info, 17));
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			texture[img->width * y + x] = img->data[img->width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img);
	return (1);
}

int		load_texture(t_info *info)
{
	t_img	img;

	if (load_image(info, info->texture[0],
			info->north_texture_path, &img) == -1)
		return (-1);
	if (load_image(info, info->texture[1],
			info->south_texture_path, &img) == -1)
		return (-1);
	if (load_image(info, info->texture[2],
			info->west_texture_path, &img) == -1)
		return (-1);
	if (load_image(info, info->texture[3],
			info->east_texture_path, &img) == -1)
		return (-1);
	if (load_image(info, info->texture[4],
			info->sprite_texture_path, &img) == -1)
		return (-1);
	free_texture_paths(info);
	return (1);
}
