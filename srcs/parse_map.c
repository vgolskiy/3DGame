/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 07:34:30 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 11:08:41 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_map(t_info *info, t_list *lst)
{
	int	tmp;

	if (init_map(info, lst) == -1)
		return (-1);
	if (fill_map(info, lst) == -1)
		return (-1);
	ft_lstclear(&lst, free);
	if (!check_valid_map(info))
		return (exit_error(info, 13));
	info->map_2d = info->map;
	if (!(info->map = transform_map(info)))
		return (exit_error(info, 7));
	tmp = info->map_height;
	info->map_height = info->map_width;
	info->map_width = tmp;
	return (1);
}

int	read_map(t_info *info, char *line)
{
	t_list	*lst;

	lst = ft_lstnew(ft_strdup(line));
	line = ft_free(line);
	while (get_next_line(info->fd, &line) > 0)
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(line)));
		line = ft_free(line);
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup(line)));
	line = ft_free(line);
	if (parse_map(info, lst) == -1)
		return (-1);
	return (1);
}

/*
** Putting player to the middle of map square
** using 0.5f instead of 0.5 to get float not double
*/

int	init_direction(t_info *info, int i, int j, int *dir_count)
{
	if (is_dir(info->map[i][j]))
	{
		info->dir = info->map[i][j];
		info->player.y = 0.5f + j;
		info->player.x = 0.5f + i;
		(*dir_count)++;
	}
	if (info->map[i][j] == '2')
		info->num_sprite++;
	return (1);
}

int	fill_map(t_info *info, t_list *lst)
{
	int		i;
	int		j;
	char	*line;
	int		dir_count;

	i = -1;
	dir_count = 0;
	while (++i < info->map_height)
	{
		j = -1;
		line = (char *)lst->content;
		while (++j < (int)ft_strlen(line))
		{
			if (!is_map_arg(line[j]))
				return (exit_error(info, 10));
			info->map[i][j] = line[j];
			init_direction(info, i, j, &dir_count);
		}
		lst = lst->next;
	}
	if (dir_count == 0)
		return (exit_error(info, 11));
	if (dir_count > 1)
		return (exit_error(info, 12));
	return (1);
}

int	check_valid_map(t_info *info)
{
	if ((!first_last_rows(info)) ||
		(!first_last_columns(info)) ||
		(!main_part(info)))
		return (0);
	return (1);
}
