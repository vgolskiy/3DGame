/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:35:48 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/11 02:20:10 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

/*
** get_next_line.c
*/

char	*str_dup_cat(char *s1, char *s2);
int		get_line(char *lines, char **line, char *found_chr);
char	*read_lines(int fd, char **line, char *lines);
int		get_next_line(int fd, char **line);

#endif
