/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:19:53 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/17 11:08:41 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_exit(int ret)
{
	exit(ret);
	return (ret);
}

void	*ft_free(void *s)
{
	if (s)
		free(s);
	return (00);
}

char	**ft_free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (00);
}

char	**ft_free_2d_broken(char **str, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (00);
}

int		**ft_free_2d_int(int **str, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (00);
}
