/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_draw_frame_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 05:21:31 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/03 05:57:49 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"

int			cb_direction(double ray)
{
	if (ray < 0)
		return (-1);
	else
		return (1);
}

double		cb_delta_dist(double ray)
{
	return (cb_direction(ray) / ray);
}
