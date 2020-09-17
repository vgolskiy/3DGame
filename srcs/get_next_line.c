/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:35:52 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 11:08:41 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

/*
** return (1): line has been read.
** return (0): EOF has been reached.
** return (-1): an error happend.
** read without newline.
*/

char	*str_dup_cat(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (00);
	len = (int)ft_strlen(s1) + (int)ft_strlen(s2);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (00);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	free(s1);
	s1 = 0;
	j = -1;
	while (s2[++j])
		res[i + j] = s2[j];
	res[len] = '\0';
	return (res);
}

int		get_line(char *lines, char **line, char *found_chr)
{
	*line = ft_substr(lines, 0, found_chr - lines);
	++found_chr;
	ft_memmove(lines, found_chr, ft_strlen(found_chr) + 1);
	return (1);
}

char	*read_lines(int fd, char **line, char *lines)
{
	char		*found_chr;
	int			bytes;
	char		buf[BUFFER_SIZE + 1];

	while (((bytes = (int)read(fd, buf, BUFFER_SIZE)) > 0))
	{
		buf[bytes] = '\0';
		if (!(lines = str_dup_cat(lines, buf)))
			return (00);
		if ((found_chr = ft_strchr(lines, '\n')))
		{
			get_line(lines, line, found_chr);
			return (lines);
		}
	}
	if (lines)
	{
		*line = ft_strdup(lines);
		free(lines);
		lines = 00;
		return (00);
	}
	*line = ft_strdup("");
	return (00);
}

int		get_next_line(int fd, char **line)
{
	static char	*lines;
	char		*found_chr;

	if ((!fd) || (fd > 65536) || (!line)
		|| (BUFFER_SIZE < 1) || (read(fd, 00, 0) < 0))
		return (-1);
	if (lines && (found_chr = ft_strchr(lines, '\n')))
		return (get_line(lines, line, found_chr));
	if ((lines = read_lines(fd, line, lines)))
		return (1);
	return (0);
}
