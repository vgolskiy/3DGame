/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 17:09:52 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 00:44:44 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	args_verif(int i, char *file, t_info *info)
{
	if ((i < 2) || ((!ft_strncmp(file, "--save", 6)) && (i == 2)))
		return (exit_error(info, 1));
	if (i > 3)
		return (exit_error(info, 2));
	if (ft_strncmp(file + (ft_strlen(file) - 4), ".cub", 4))
		return (exit_error(info, 3));
	return (1);
}

static void	get_screen_resolution(t_info *info)
{
	int	width;
	int hight;

	width = 0;
	hight = 0;
	mlx_get_screen_size(info->mlx, &width, &hight);
	info->width = info->width > width ? width : info->width;
	info->height = info->height > hight - 50 ? hight - 50 : info->height;
}

static int	set_info(t_info *info, char *path)
{
	init_player(&info->player);
	if (parse_cub(info, path) == -1)
		return (-1);
	init_player_direction(info);
	if (!(info->mlx = mlx_init()))
		return (exit_error(info, 15));
	get_screen_resolution(info);
	if (init_buffer(info) == -1)
		return (-1);
	if (init_texture(info) == -1)
		return (-1);
	if (load_texture(info) == -1)
		return (-1);
	if (!(info->img.img = mlx_new_image(info->mlx,
					info->width, info->height)))
		return (exit_error(info, 15));
	if (!(info->img.data = (int *)mlx_get_data_addr(info->img.img,
			&info->img.bpp, &info->img.size_l, &info->img.endian)))
		return (exit_error(info, 15));
	return (1);
}

static int	process_option(t_info *info, int option)
{
	if (option == 1)
	{
		raycasting(info);
		sprite_raycasting(info, &info->player);
		if (save_bmp(info) == -1)
			return (-1);
	}
	else
	{
		if (!(info->win = mlx_new_window(info->mlx,
							info->width, info->height, "cub3d")))
			return (exit_error(info, 15));
		mlx_hook(info->win, X_EVENT_KEY_PRESS, 0, key_press, info);
		mlx_hook(info->win, X_EVENT_KEY_EXIT, 0, ft_exit, 0);
		mlx_loop_hook(info->mlx, main_loop, info);
		mlx_loop(info->mlx);
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_info	info;
	int		option;

	option = 0;
	init_info(&info);
	if (args_verif(argc, argv[1], &info) == -1)
		return (-1);
	if (argc == 3)
	{
		if (!ft_strncmp(argv[2], "--save", 6))
			option = 1;
		else
			return (exit_error(&info, 4));
	}
	if (set_info(&info, argv[1]) == -1)
		return (-1);
	if (process_option(&info, option) == -1)
		return (-1);
	free_cub(&info);
	return (0);
}
