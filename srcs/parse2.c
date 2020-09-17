/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 03:15:28 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 11:08:41 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	verify_number(char **str, int rows)
{
	int	i;
	int	j;

	i = -1;
	while (++i < rows)
	{
		j = 0;
		while ((str[i][j]) && (ft_isspace(str[i][j])))
			j++;
		if (!ft_isdigit(str[i][j]))
			return (0);
	}
	return (1);
}

int	get_color(t_info *info, char *line, int direction)
{
	char	**rgb;
	int		color;

	while ((line) && (ft_isspace(*line)))
		line++;
	if ((line) && (!ft_isdigit(*line)))
		return (exit_error(info, 9));
	if (!(rgb = ft_split(line, ',')))
		return (exit_error(info, 7));
	if (!rgb[0] || !rgb[1] || !rgb[2]
		|| (!verify_number(rgb, 3)))
		return (exit_error(info, 9));
	if ((ft_atoi(rgb[0]) > 255) || (ft_atoi(rgb[1]) > 255)
		|| (ft_atoi(rgb[2]) > 255))
		return (exit_error(info, 9));
	color = color_pack(0, ft_atoi(rgb[0]),
					ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	rgb = ft_free_2d(rgb);
	if (direction == 'F')
		info->floor_color = color;
	else if (direction == 'C')
		info->ceiling_color = color;
	direction == 'F' ? info->set[6]++ : info->set[7]++;
	return (1);
}
