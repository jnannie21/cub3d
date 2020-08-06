/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_draw_walls_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 05:41:50 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/06 02:20:04 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cb_cub3d.h"

void			cb_draw_wall_line(t_cbdata *cb, t_cbimage *texture)
{
	double			tex_step_y;
	t_cbscreen		*sc;
	t_cbraycaster	*rc;

	sc = cb->sc;
	rc = cb->rc;
	sc->line_height = (int)(cb->frame->height / rc->perp_dists[sc->frame_x]);
	tex_step_y = (double)texture->height / sc->line_height;
	sc->frame_start_y = (-sc->line_height + cb->frame->height) / 2;
	sc->frame_end_y = (sc->line_height + cb->frame->height) / 2;
	sc->tex_y = (sc->frame_start_y < 0)
		? tex_step_y * (-sc->frame_start_y) : 0;
	sc->frame_start_y = (sc->frame_start_y < 0) ? 0 : sc->frame_start_y;
	sc->frame_end_y = (sc->frame_end_y >= cb->frame->height)
		? (cb->frame->height - 1) : sc->frame_end_y;
	sc->frame_y = sc->frame_start_y - 1;
	while (++sc->frame_y <= sc->frame_end_y)
	{
		sc->frame_pix = sc->frame_y * cb->frame->size_line / 4 + sc->frame_x;
		sc->tex_pix = (int)(sc->tex_y + (sc->frame_y - sc->frame_start_y)
			* tex_step_y) * texture->size_line / 4 + sc->tex_x;
		((int *)(cb->frame->image))[sc->frame_pix] =
			((int *)(texture->image))[sc->tex_pix];
	}
}

double			cb_wall_coord(t_cbdata *cb)
{
	double wall_x;

	if (cb->rc->wall_side == 0)
		wall_x = cb->pos_y + cb->rc->perp_dists[cb->sc->frame_x]
			* cb->rc->ray_y;
	else
		wall_x = cb->pos_x + cb->rc->perp_dists[cb->sc->frame_x]
			* cb->rc->ray_x;
	wall_x -= floor((wall_x));
	return (wall_x);
}

void			cb_find_wall(t_cbdata *cb, t_cbraycaster *rc)
{
	while (cb->map[rc->map_y][rc->map_x] != '1')
		if (rc->dist_x < rc->dist_y)
		{
			rc->dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->wall_side = 0;
		}
		else
		{
			rc->dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->wall_side = 1;
		}
}
