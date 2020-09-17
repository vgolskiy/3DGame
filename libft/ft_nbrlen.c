/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:01:38 by mskinner          #+#    #+#             */
/*   Updated: 2020/09/11 01:56:19 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbrlen(long long n)
{
	int	len;

	len = 1;
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}