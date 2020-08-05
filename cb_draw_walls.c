/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_draw_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 05:24:04 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/05 05:45:16 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"

static void		cb_init_vars(t_cbdata *cb, t_cbraycaster *rc, t_cbscreen *sc)
{
	rc->ray_x = cb->dir_x + cb->plane_x * (-1 + rc->plane_step * sc->frame_x);
	rc->ray_y = cb->dir_y + cb->plane_y * (-1 + rc->plane_step * sc->frame_x);
	rc->map_x = (int)(cb->pos_x);
	rc->map_y = (int)(cb->pos_y);
	rc->step_x = (rc->ray_x < 0) ? -1 : 1;
	rc->step_y = (rc->ray_y < 0) ? -1 : 1;
	rc->delta_dist_x = rc->step_x / rc->ray_x;
	rc->delta_dist_y = rc->step_y / rc->ray_y;
	if (rc->ray_x < 0)
		rc->dist_x = (cb->pos_x - rc->map_x) * rc->delta_dist_x;
	else
		rc->dist_x = (rc->map_x + 1.0 - cb->pos_x) * rc->delta_dist_x;
	if (rc->ray_y < 0)
		rc->dist_y = (cb->pos_y - rc->map_y) * rc->delta_dist_y;
	else
		rc->dist_y = (rc->map_y + 1.0 - cb->pos_y) * rc->delta_dist_y;
}

static t_cbimage	*cb_select_texture(t_cbdata *cb, t_cbraycaster *rc)
{
	t_cbimage		*texture;

	if (rc->wall_side == 0 && rc->ray_x > 0)
		texture = cb->we_texture;
	else if (rc->wall_side == 0 && rc->ray_x < 0)
		texture = cb->ea_texture;
	else if (rc->wall_side == 1 && rc->ray_y > 0)
		texture = cb->no_texture;
	else if (rc->wall_side == 1 && rc->ray_y < 0)
		texture = cb->so_texture;
	return (texture);
}

static void		cb_calc_perp_dist(t_cbdata *cb, t_cbraycaster *rc,
									t_cbscreen *sc)
{
	if (rc->wall_side == 0)
		rc->perp_dists[sc->frame_x] = (rc->map_x - cb->pos_x
			+ (1 - rc->step_x) / 2) / rc->ray_x;
	else
		rc->perp_dists[sc->frame_x] = (rc->map_y - cb->pos_y
			+ (1 - rc->step_y) / 2) / rc->ray_y;
}

static void		cb_calc_texx(t_cbdata *cb, t_cbimage *texture,
							t_cbraycaster *rc, t_cbscreen *sc)
{
	sc->tex_x = (int)(cb_wall_coord(cb) * texture->width);
	if ((rc->wall_side == 0 && rc->ray_x < 0) ||
		(rc->wall_side == 1 && rc->ray_y > 0))
		sc->tex_x = texture->width - sc->tex_x - 1;

}

void			cb_draw_walls(t_cbdata *cb)
{
	t_cbimage		*texture;
	t_cbraycaster	*rc;
	t_cbscreen		*sc;

	rc = cb->rc;
	sc = cb->sc;
	sc->frame_x = 0;
	rc->plane_step = 2.0 / cb->frame->width;
	while (sc->frame_x < cb->frame->width)
	{
		cb_init_vars(cb, rc, sc);
		cb_find_wall(cb, rc);
		cb_calc_perp_dist(cb, rc, sc);
		texture = cb_select_texture(cb, rc);
		cb_calc_texx(cb, texture, rc, sc);
		cb_draw_wall_line(cb, texture);
		sc->frame_x++;
	}
}
