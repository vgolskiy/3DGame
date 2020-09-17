/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_get_screen_size.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 18:18:37 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/09 15:37:01 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CoreGraphics/CoreGraphics.h>
#include <OpenGL/OpenGL.h>

void	mlx_get_screen_size(void *mlx_ptr, int *x, int *y)
{
	CGRect	mainMonitor;

	(void) mlx_ptr;
	mainMonitor = CGDisplayBounds(CGMainDisplayID());
	*x = CGRectGetWidth(mainMonitor);
	*y = CGRectGetHeight(mainMonitor);
	return ;
}
