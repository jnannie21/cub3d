/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_motion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 10:11:38 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/05 21:43:47 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"

#define CB_INDENTATION 2

void			cb_rotate_vectors(t_cbdata *cb, double angle)
{
	double			temp_x;
	double			temp_y;
	static double	cosine;
	static double	sine;
	static double	last_angle;

	if ((sine == 0 && cosine == 0) || last_angle != angle)
	{
		cosine = cos(angle);
		sine = sin(angle);
	}
	last_angle = angle;
	temp_x = cb->dir_x;
	temp_y = cb->dir_y;
	cb->dir_x = temp_x * cosine - temp_y * sine;
	cb->dir_y = temp_x * sine + temp_y * cosine;
	temp_x = cb->dir_x_perp;
	temp_y = cb->dir_y_perp;
	cb->dir_x_perp = temp_x * cosine - temp_y * sine;
	cb->dir_y_perp = temp_x * sine + temp_y * cosine;
	temp_x = cb->plane_x;
	temp_y = cb->plane_y;
	cb->plane_x = temp_x * cosine - temp_y * sine;
	cb->plane_y = temp_x * sine + temp_y * cosine;
}

void			cb_move(t_cbdata *cb, double dir_x, double dir_y, int dir)
{
	int				dx;
	int				dy;
	double			indent;
	double			move_speed;

	dx = dir_x < 0 ? -1 : 1;
	dy = dir_y < 0 ? -1 : 1;
	move_speed = cb->move_speed * dir;
	indent = move_speed * dx * CB_INDENTATION;
	if (cb->map[(int)(cb->pos_y)][(int)(cb->pos_x + indent)] != '1')
		cb->pos_x += dir_x * move_speed;
	indent = move_speed * dy * CB_INDENTATION;
	if (cb->map[(int)(cb->pos_y + indent)][(int)(cb->pos_x)] != '1')
		cb->pos_y += dir_y * move_speed;
}
