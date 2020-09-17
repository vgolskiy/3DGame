/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 07:31:33 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 11:08:41 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Verification logic:
** - zeros should be surrounded by other zeros or ones/NEWS indices, so
** any surrounding number should be more or equal to zero;
** - we will verify neighbours clockwise (including diagonal positions);
** - it is very important to avoid getting out of matrix indices range
** while verification, so we will use (1, rows/columns ranges - 1)
** for our variables;
** - all matrix elements on the first/last rows/columns should be -1 / 1.
*/

int			first_last_rows(t_info *info)
{
	int i;
	int j;

	i = 0;
	while (i < info->map_height)
	{
		j = 0;
		while (j < info->map_width)
		{
			if ((info->map[i][j] == '0') || (is_dir(info->map[i][j]))
				|| (info->map[i][j] == '2'))
				return (0);
			j++;
		}
		i += info->map_height - 1;
	}
	return (1);
}

int			first_last_columns(t_info *info)
{
	int i;
	int j;

	j = 0;
	while (j < info->map_width)
	{
		i = 0;
		while (i < info->map_height)
		{
			if ((info->map[i][j] == '0') || (is_dir(info->map[i][j]))
				|| (info->map[i][j] == '2'))
				return (0);
			i++;
		}
		j += info->map_width - 1;
	}
	return (1);
}

int			watch_around(t_info *info, int pos_i, int pos_j)
{
	int i;
	int j;

	i = pos_i - 1;
	while (i <= pos_i + 1)
	{
		j = pos_j - 1;
		while (j <= pos_j + 1)
		{
			if ((info->map[i][j] == ' ') || (info->map[i][j] == '\n')
				|| (info->map[i][j] == '\0'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int			main_part(t_info *info)
{
	int i;
	int j;

	i = 1;
	while (i < info->map_height - 1)
	{
		j = 1;
		while (j < info->map_width - 1)
		{
			while (((info->map[i][j] == '1')
			|| (info->map[i][j] == ' ') || (info->map[i][j] == '\n')
			|| (info->map[i][j] == '\0'))
			&& (j < info->map_width - 1))
				j++;
			if (((info->map[i][j] == '0') || (is_dir(info->map[i][j])))
			&& (j < info->map_width - 1))
				if (!watch_around(info, i, j))
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}
