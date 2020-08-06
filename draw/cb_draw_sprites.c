/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_draw_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 04:50:17 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/07 00:13:25 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cb_cub3d.h"

static void		cb_sort_sprites(t_cbdata *cb)
{
	int			i;
	int			j;
	int			found;
	t_sprite	temp;

	j = 0;
	found = 1;
	while (j < cb->sprites_num - 1 && found)
	{
		found = 0;
		i = 0;
		while (i < cb->sprites_num - 1 - j)
		{
			if (cb->sprites[i].dist < cb->sprites[i + 1].dist)
			{
				temp = cb->sprites[i];
				cb->sprites[i] = cb->sprites[i + 1];
				cb->sprites[i + 1] = temp;
				found = 1;
			}
			i++;
		}
		j++;
	}
}

static void		cb_draw_sprite_lines(t_cbdata *cb, int sprite_screen_x,
									double sprite_y, t_cbscreen *sc)
{
	int			pixel;

	sc->frame_x = sc->frame_start_x - 1;
	while (++sc->frame_x < sc->frame_end_x)
	{
		sc->tex_x = (int)((sc->frame_x - (-sc->line_width / 2
			+ sprite_screen_x)) * cb->sprite->width / sc->line_width);
		sc->frame_y = sc->frame_start_y;
		if (sprite_y > 0.0 && sc->frame_x > 0
			&& sc->frame_x < cb->frame->width
			&& sprite_y < cb->rc->perp_dists[sc->frame_x])
			while (++sc->frame_y < sc->frame_end_y)
			{
				sc->tex_y = ((double)(sc->frame_y
					- (cb->frame->height - sc->line_height) / 2)
					* cb->sprite->height) / sc->line_height;
				pixel = *((int *)(cb->sprite->image + cb->sprite->size_line
					* sc->tex_y + sc->tex_x * 4));
				if ((pixel & 0x00FFFFFF))
					*((int *)(cb->frame->image + cb->frame->size_line
						* sc->frame_y + sc->frame_x * 4)) = pixel;
			}
	}
}

static void		cb_calc_frame(t_cbdata *cb, double sprite_y,
							int sprite_screen_x, t_cbscreen *sc)
{
	sc->line_height = abs((int)(cb->frame->height / (sprite_y)));
	sc->frame_start_y = -sc->line_height / 2 + cb->frame->height / 2;
	if (sc->frame_start_y < 0)
		sc->frame_start_y = 0;
	sc->frame_end_y = sc->line_height / 2 + cb->frame->height / 2;
	if (sc->frame_end_y >= cb->frame->height)
		sc->frame_end_y = cb->frame->height - 1;
	sc->line_width = abs((int)(cb->frame->height / (sprite_y)));
	sc->frame_start_x = -sc->line_width / 2 + sprite_screen_x;
	if (sc->frame_start_x < 0)
		sc->frame_start_x = 0;
	sc->frame_end_x = sc->line_width / 2 + sprite_screen_x;
	if (sc->frame_end_x >= cb->frame->width)
		sc->frame_end_x = cb->frame->width - 1;
}

/*
** sprite_x = sprite_x / sprite_y / CB_PLANE_LENGTH mean take projection on plane (sprite_x / sprite_y)
** and scale it to [-1; 1] (/ CB_PLANE_LENGTH)
*/

void			cb_draw_sprites(t_cbdata *cb)
{
	int			i;
	int			sprite_screen_x;
	double		sprite_x;
	double		sprite_y;

	i = -1;
	while (++i < cb->sprites_num)
		cb->sprites[i].dist = ((cb->pos_x - cb->sprites[i].x)
			* (cb->pos_x - cb->sprites[i].x) + (cb->pos_y - cb->sprites[i].y)
			* (cb->pos_y - cb->sprites[i].y));
	cb_sort_sprites(cb);
	i = -1;
	while (++i < cb->sprites_num)
	{
		sprite_x = -cb->dir_x_perp * (cb->sprites[i].x - cb->pos_x)
			+ -cb->dir_y_perp * (cb->sprites[i].y - cb->pos_y);
		sprite_y = cb->dir_y_perp * (cb->sprites[i].x - cb->pos_x)
			+ -cb->dir_x_perp * (cb->sprites[i].y - cb->pos_y);
		sprite_x = sprite_x / sprite_y / CB_PLANE_LENGTH;
		sprite_screen_x = (int)((cb->frame->width / 2) * (1 - sprite_x));
		cb_calc_frame(cb, sprite_y, sprite_screen_x, cb->sc);
		cb_draw_sprite_lines(cb, sprite_screen_x, sprite_y, cb->sc);
	}
}
