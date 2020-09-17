/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:15:43 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 11:08:41 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_info(t_info *info)
{
	ft_memset(info->set, 0, sizeof(info->set));
	info->mlx = 00;
	info->win = 00;
	info->img.img = 00;
	info->sprite = 00;
	info->buf = 00;
	info->z_buffer = 00;
	info->texture = 00;
	info->width = 0;
	info->height = 0;
	info->map_width = 0;
	info->map_height = 0;
	info->map = 00;
	info->map_2d = 00;
	info->north_texture_path = 00;
	info->south_texture_path = 00;
	info->west_texture_path = 00;
	info->east_texture_path = 00;
	info->sprite_texture_path = 00;
	info->floor_color = 0;
	info->ceiling_color = 0;
	info->num_sprite = 0;
}

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->dir_x = -1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.66;
	player->move_speed = 0.05;
	player->rot_speed = 0.05;
}

int		init_buffer(t_info *info)
{
	int	i;

	i = 0;
	if (!(info->buf = ft_calloc(info->height, sizeof(int **))))
		return (exit_error(info, 7));
	while (i < info->height)
	{
		if (!(info->buf[i] = ft_calloc(info->width, sizeof(int *))))
		{
			while (--i >= 0)
				free(info->buf[i]);
			free(info->buf);
			info->buf = 00;
			return (exit_error(info, 7));
		}
		i++;
	}
	if (!(info->z_buffer = ft_calloc(info->width, sizeof(double *))))
		return (exit_error(info, 7));
	return (1);
}

int		init_texture(t_info *info)
{
	int	i;
	int	j;

	if (!(info->texture = (int **)malloc(sizeof(int *) * 5)))
		return (exit_error(info, 7));
	i = 0;
	while (i < 6)
	{
		if (!(info->texture[i] = (int *)malloc(sizeof(int)
					* (TEX_HEIGHT * TEX_WIDTH))))
		{
			info->texture = ft_free_2d_int(info->texture, --i);
			return (exit_error(info, 7));
		}
		j = 0;
		while (j < TEX_HEIGHT * TEX_WIDTH)
		{
			info->texture[i][j] = 0;
			j++;
		}
		i++;
	}
	return (1);
}

int		init_map(t_info *info, t_list *lst)
{
	int	i;
	int	j;

	info->map_height = ft_lstsize(lst);
	if (!(info->map = (char **)malloc(sizeof(char *) * (info->map_height + 1))))
		return (exit_error(info, 7));
	i = 0;
	info->map_width = get_max_line_size(lst);
	while (lst)
	{
		if (!(info->map[i] = (char *)ft_calloc(sizeof(char),
				(info->map_width + 1))))
		{
			info->map = ft_free_2d_broken(info->map, --i);
			return (exit_error(info, 7));
		}
		j = (int)ft_strlen(lst->content);
		while (j++ < info->map_width)
			info->map[i][j] = ' ';
		info->map[i][info->map_width] = '\0';
		i++;
		lst = lst->next;
	}
	info->map[i] = 00;
	return (1);
}
