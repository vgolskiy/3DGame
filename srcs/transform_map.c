/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 07:31:33 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 11:08:41 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Changing map to avoid mirror effect
*/

char		**init_transformed_map(t_info *info)
{
	int		i;
	char	**map;

	if (!(map = (char **)malloc(sizeof(char *) * (info->map_width + 1))))
		return (00);
	i = 0;
	while (i < info->map_width)
	{
		if (!(map[i] = (char *)malloc(sizeof(char) * (info->map_height + 1))))
			return (ft_free_2d_broken(map, --i));
		i++;
	}
	map[i] = 00;
	return (map);
}

char		**transform_map(t_info *info)
{
	int		i;
	int		j;
	char	**map;

	if (!(map = init_transformed_map(info)))
		return (00);
	i = -1;
	while (++i < info->map_width)
	{
		j = -1;
		while (++j < info->map_height)
			map[i][j] = info->map[j][i];
		map[i][j] = '\0';
	}
	return (map);
}
