/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 07:35:23 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 11:08:41 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** 1) Error\nPlease, put map to arguments
** 2) Error\nToo many arguments
** 3) Error\nPlease, put map to first argument
** 4) Error\nWrong flag in arguments
** 5) Error\nFile couldn't be opened
** 6) Error\nWrong screen resolution
** 7) Error\nMalloc failed
** 8) Error\nWrong texture path
** 9) Error\nWrong color identificator
** 10) Error\nWrong map argument
** 11) Error\nThere is no player on the map
** 12) Error\nMultiplayer is not allowed
** 13) Error\nMap is not closed
** 14) Error\nSettings are not properly defined
** 15) Error\nMLX was not initiated
** 16) Error\nImage file was not created
** 17) Error\nTexture was not uploaded
** 18) Error\nCould not write to file
*/

t_error		g_err[] =
{
	{"Error\nPlease, put map to arguments"},
	{"Error\nToo many arguments"},
	{"Error\nPlease, put valid map to first argument"},
	{"Error\nWrong flag in arguments"},
	{"Error\nFile couldn't be opened"},
	{"Error\nWrong screen resolution"},
	{"Error\nMalloc failed"},
	{"Error\nWrong texture path"},
	{"Error\nWrong color identificator"},
	{"Error\nWrong map argument"},
	{"Error\nThere is no player on the map"},
	{"Error\nMultiplayer is not allowed"},
	{"Error\nMap is not closed"},
	{"Error\nSettings are not properly defined"},
	{"Error\nMLX was not initiated"},
	{"Error\nImage file was not created"},
	{"Error\nTexture was not uploaded"},
	{"Error\nCould not write to file"}
};

int		exit_error(t_info *info, int err)
{
	if (err)
	{
		write(2, g_err[err - 1].desc,
		ft_strlen(g_err[err - 1].desc));
		ft_putchar('\n');
	}
	if (info->fd)
		close(info->fd);
	free_cub(info);
	return (-1);
}

int		check_init(t_info *info)
{
	int	i;

	i = -1;
	while (++i < 8)
		if ((!info->set[i]) || (info->set[i] > 1))
			return (0);
	if ((!info->map_width) || (!info->map_height) ||
		(!info->north_texture_path) || (!info->south_texture_path) ||
		(!info->west_texture_path) || (!info->east_texture_path) ||
		(!info->sprite_texture_path) || (!info->floor_color) ||
		(!info->ceiling_color))
		return (0);
	return (1);
}

int		is_dir(int c)
{
	if ((c == 'N') || (c == 'S') ||
		(c == 'E') || (c == 'W'))
		return (1);
	return (0);
}

int		is_map_arg(int c)
{
	if ((is_dir(c)) || (c == ' ') ||
		((c >= '0') && (c <= '2')) ||
		(c == '\n') || (c == '\0'))
		return (1);
	return (0);
}
