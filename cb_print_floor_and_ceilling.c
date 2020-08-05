/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_print_floor_and_ceilling.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 05:27:42 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/05 05:29:11 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"

void			cb_print_floor_and_ceilling(t_cbdata *cb)
{
	int		height;
	int		width;
	int		*image;

	height = 0;
	width = 0;
	image = (int *)cb->frame->image;
	while (height < cb->frame->height)
	{
		while (width < cb->frame->width)
		{
			if (height < cb->frame->height / 2)
				*image = cb->ceilling_color;
			else
				*image = cb->floor_color;
			image++;
			width++;
		}
		width = 0;
		height++;
	}
}
