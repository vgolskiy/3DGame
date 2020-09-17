/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 03:15:28 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 11:08:41 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_screen_size(t_info *info, char *line)
{
	char	**size;

	while ((line) && (ft_isspace(*line)))
		line++;
	if ((line) && (!ft_isdigit(*line)))
		return (exit_error(info, 6));
	if (!(size = ft_split(line, ' ')))
		return (exit_error(info, 7));
	if ((!size[0]) || (!size[1])
		|| (!verify_number(size, 2)))
		return (exit_error(info, 6));
	info->width = ft_atoi(size[0]);
	info->height = ft_atoi(size[1]);
	size = ft_free_2d(size);
	if (!info->width || !info->height)
		return (exit_error(info, 6));
	if ((info->width < 450) || (info->height < 300))
		write(1,
		"Resolution was changed to the minimal appropriate 450x300\n", 58);
	info->width = info->width < 450 ? 450 : info->width;
	info->height = info->height < 300 ? 300 : info->height;
	info->set[0]++;
	return (1);
}

int	get_texture(t_info *info, char *line, char *direction)
{
	while ((line) && (ft_isspace(*line)))
		line++;
	if ((line) && (*line == '\0'))
		return (exit_error(info, 8));
	else if (!ft_strncmp(direction, "NO", 2))
		info->north_texture_path = ft_strdup(line);
	else if (!ft_strncmp(direction, "SO", 2))
		info->south_texture_path = ft_strdup(line);
	else if (!ft_strncmp(direction, "WE", 2))
		info->west_texture_path = ft_strdup(line);
	else if (!ft_strncmp(direction, "EA", 2))
		info->east_texture_path = ft_strdup(line);
	else if (!ft_strncmp(direction, "S", 1))
		info->sprite_texture_path = ft_strdup(line);
	if (!ft_strncmp(direction, "NO", 2))
		info->set[1]++;
	else if (!ft_strncmp(direction, "SO", 2))
		info->set[2]++;
	else if (!ft_strncmp(direction, "WE", 2))
		info->set[3]++;
	else if (!ft_strncmp(direction, "EA", 2))
		info->set[4]++;
	else if (!ft_strncmp(direction, "S", 1))
		info->set[5]++;
	return (1);
}

int	parse_line(t_info *info, char *line)
{
	if (!ft_strncmp(line, "R ", 2))
		return (get_screen_size(info, line + 2));
	else if (!ft_strncmp(line, "NO ", 3))
		return (get_texture(info, line + 3, "NO"));
	else if (!ft_strncmp(line, "SO ", 3))
		return (get_texture(info, line + 3, "SO"));
	else if (!ft_strncmp(line, "WE ", 3))
		return (get_texture(info, line + 3, "WE"));
	else if (!ft_strncmp(line, "EA ", 3))
		return (get_texture(info, line + 3, "EA"));
	else if (!ft_strncmp(line, "S ", 2))
		return (get_texture(info, line + 2, "S"));
	else if (!ft_strncmp(line, "F ", 2))
		return (get_color(info, line + 2, 'F'));
	else if (!ft_strncmp(line, "C ", 2))
		return (get_color(info, line + 2, 'C'));
	else if (line[0] == '\0')
		return (1);
	return (0);
}

int	parse_cub(t_info *info, char *path)
{
	char	*line;
	int		ret;
	int		n;

	info->fd = open(path, O_RDONLY);
	while ((n = get_next_line(info->fd, &line)) > 0)
	{
		if ((ret = parse_line(info, line)) == -1)
			return (-1);
		if (!ret)
			break ;
		line = ft_free(line);
	}
	if (n < 0)
		return (exit_error(info, 5));
	if (read_map(info, line) == -1)
		return (-1);
	if (!check_init(info))
		return (exit_error(info, 14));
	if (set_sprite(info) == -1)
		return (-1);
	return (1);
}
