/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 09:55:49 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 11:08:41 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				*color_unpack(int color)
{
	int	*clr;

	if (!(clr = (int *)malloc(4 * sizeof(int))))
		return (00);
	clr[0] = (color >> 24) & 255;
	clr[1] = (color >> 16) & 255;
	clr[2] = (color >> 8) & 255;
	clr[3] = (color >> 0) & 255;
	return (clr);
}

int				bmp_header(t_info *info, uint32_t imagesize,
						uint16_t bitcount)
{
	uint32_t		b_size;
	uint32_t		b_offset;
	uint32_t		filesize;
	uint16_t		b_planes;
	unsigned char	header[54];

	b_size = 40;
	b_offset = 54;
	filesize = 54 + imagesize;
	b_planes = 1;
	ft_memset(header, (unsigned char)0, sizeof(header));
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 2, &filesize, 4);
	ft_memcpy(header + 10, &b_offset, 4);
	ft_memcpy(header + 14, &b_size, 4);
	ft_memcpy(header + 18, &info->width, 4);
	ft_memcpy(header + 22, &info->height, 4);
	ft_memcpy(header + 26, &b_planes, 2);
	ft_memcpy(header + 28, &bitcount, 2);
	ft_memcpy(header + 34, &imagesize, 4);
	if (write(info->fd, header, b_offset) < b_offset)
		return (exit_error(info, 18));
	return (1);
}

int				fill_buf(t_info *info, unsigned char *buf,
						int width_in_bytes)
{
	int	i;
	int	j;
	int	*clr;

	i = info->height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < info->width)
		{
			if (!(clr = color_unpack(info->buf[i][j])))
				return (exit_error(info, 7));
			buf[((info->height - 1) - i) * width_in_bytes + j * 3 + 0] = clr[3];
			buf[((info->height - 1) - i) * width_in_bytes + j * 3 + 1] = clr[2];
			buf[((info->height - 1) - i) * width_in_bytes + j * 3 + 2] = clr[1];
			clr = ft_free(clr);
			j++;
		}
		i--;
	}
	return (1);
}

int				save_bmp2(t_info *info, uint32_t imagesize,
						int width_in_bytes)
{
	unsigned char	*buf;

	if (!(buf = (unsigned char *)malloc(imagesize * sizeof(unsigned char))))
		return (exit_error(info, 7));
	if (fill_buf(info, buf, width_in_bytes) == -1)
	{
		free(buf);
		return (-1);
	}
	if (write(info->fd, buf, imagesize) < imagesize)
	{
		free(buf);
		return (exit_error(info, 18));
	}
	free(buf);
	close(info->fd);
	return (1);
}

int				save_bmp(t_info *info)
{
	uint16_t		bitcount;
	int				width_in_bytes;
	uint32_t		imagesize;

	bitcount = 24;
	width_in_bytes = ((info->width * bitcount + 31) / 32) * 4;
	imagesize = width_in_bytes * info->height;
	info->fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (info->fd < 0)
		return (exit_error(info, 16));
	if (bmp_header(info, imagesize, bitcount) == -1)
		return (-1);
	if (save_bmp2(info, imagesize, width_in_bytes) == -1)
		return (-1);
	return (1);
}
