/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_draw_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 21:49:44 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/04 07:38:32 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"
#include <math.h>

/*
unsigned int		cb_color_to_big_endian(unsigned int color)
{
	unsigned int		new_color;
	unsigned int		straight_mask;
	unsigned int		inverse_mask;

	new_color = 0;
	straight_mask = 1;
	inverse_mask = 1 << 31;
	while (straight_mask)
	{
		if (color & straight_mask)
			new_color |= inverse_mask;
		straight_mask <<= 1;
		inverse_mask >>= 1;
	}
	return (new_color);
}
*/
void			cb_print_floor_and_ceilling(t_cbdata *cb)
{
	int		height;
	int		width;
	int		*image;

	height = 0;
	width = 0;
	image = (int *)cb->frame->image;
//	if (cbdata->frame->endian)
//	{
//		cbdata->floor_color = cb_color_to_big_endian(cbdata->floor_color);
//		cbdata->ceilling_color = cb_color_to_big_endian(cbdata->ceilling_color);
//	}
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

static void			cb_draw_line(t_cbdata *cb,
									t_cbimage *texture)
{
	int				frame_pix;
	int				tex_pix;
	double			tex_start_y;
	double			tex_step_y;
	t_cbraycaster	*rc;

	rc = cb->rc;
	rc->line_height = (int)(cb->frame->height / rc->perp_dists[rc->frame_x]);
	tex_step_y = (double)texture->height / rc->line_height;
	rc->frame_start_y = (-rc->line_height + cb->frame->height) / 2;
	rc->frame_end_y = (rc->line_height + cb->frame->height) / 2;
	tex_start_y = (rc->frame_start_y < 0) ?
		tex_step_y * (-rc->frame_start_y) : 0;
	rc->frame_start_y = (rc->frame_start_y < 0) ? 0 : rc->frame_start_y;
	if (rc->frame_end_y >= cb->frame->height)
		rc->frame_end_y = cb->frame->height - 1;
	rc->frame_y = rc->frame_start_y - 1;
	while (rc->frame_y++ <= rc->frame_end_y)
	{
		frame_pix = rc->frame_y * cb->frame->size_line / 4 + rc->frame_x;
		tex_pix = (int)(tex_start_y + (rc->frame_y - rc->frame_start_y) *
			tex_step_y) * texture->size_line / 4 + rc->tex_x;
		((int *)(cb->frame->image))[frame_pix] =
			((int *)(texture->image))[tex_pix];
	}
}

static double	cb_where_wall_hit(t_cbdata *cb)
{
	double wall_x; //where exactly the wall was hit

	if (cb->rc->wall_side == 0)
		wall_x = cb->pos_y + cb->rc->perp_dists[cb->rc->frame_x] * cb->rc->ray_y;
	else
		wall_x = cb->pos_x + cb->rc->perp_dists[cb->rc->frame_x] * cb->rc->ray_x;
	wall_x -= floor((wall_x));
	return (wall_x);
}

static void		cb_draw_walls(t_cbdata *cb)
{
//	int				x;
	t_cbimage		*texture;
	t_cbraycaster	*rc;

	rc = cb->rc;
	rc->frame_x = 0;
	rc->plane_step = 2.0 / cb->frame->width;
	while (rc->frame_x < cb->frame->width)
	{
		rc->ray_x = cb->dir_x + cb->plane_x * (-1 + rc->plane_step * rc->frame_x);
		rc->ray_y = cb->dir_y + cb->plane_y * (-1 + rc->plane_step * rc->frame_x);
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
		if (rc->wall_side == 0)
			rc->perp_dists[rc->frame_x] = (rc->map_x - cb->pos_x + (1 - rc->step_x) / 2) / rc->ray_x;
		else
			rc->perp_dists[rc->frame_x] = (rc->map_y - cb->pos_y + (1 - rc->step_y) / 2) / rc->ray_y;
		if (rc->wall_side == 0 && rc->ray_x > 0)
			texture = cb->we_texture;
		else if (rc->wall_side == 0 && rc->ray_x < 0)
			texture = cb->ea_texture;
		else if (rc->wall_side == 1 && rc->ray_y > 0)
			texture = cb->no_texture;
		else if (rc->wall_side == 1 && rc->ray_y < 0)
			texture = cb->so_texture;
		rc->tex_x = (int)(cb_where_wall_hit(cb) * texture->width);
		if ((rc->wall_side == 0 && rc->ray_x < 0) ||
			(rc->wall_side == 1 && rc->ray_y > 0))
			rc->tex_x = texture->width - rc->tex_x - 1;
		cb_draw_line(cb, texture);
		rc->frame_x++;
	}
}

static void		cb_draw_sprites(t_cbdata *cb)
{

	for (int i = 0; i < cb->sprites_num; i++)
		cb->sprites[i].dist = ((cb->pos_x - cb->sprites[i].x) * (cb->pos_x - cb->sprites[i].x) +
										(cb->pos_y - cb->sprites[i].y) * (cb->pos_y - cb->sprites[i].y));
	cb_sort_sprites(cb);
	for (int i = 0; i < cb->sprites_num; i++)
	{
		double spriteX = cb->sprites[i].x - cb->pos_x;
		double spriteY = cb->sprites[i].y - cb->pos_y;
		double perp_x = -cb->dir_x_perp;
		double perp_y = -cb->dir_y_perp;
		double transformX = perp_x * spriteX + perp_y * spriteY;
		double transformY = -perp_y * spriteX + perp_x * spriteY;
		transformX = transformX / transformY / 0.66;
		int spriteScreenX = cb->frame->width / 2;
		spriteScreenX = (int)((cb->frame->width / 2) * (1 - transformX));
		int spriteHeight = 0;
		spriteHeight = abs((int)(cb->frame->height / (transformY)));
		int drawStartY = -spriteHeight / 2 + cb->frame->height / 2;
		if (drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + cb->frame->height / 2;
		if (drawEndY >= cb->frame->height) drawEndY = cb->frame->height - 1;
		int spriteWidth = 0;
		spriteWidth = abs((int)(cb->frame->height / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= cb->frame->width) drawEndX = cb->frame->width - 1;
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)((stripe - (-spriteWidth / 2 + spriteScreenX)) * cb->sprite->width / spriteWidth);
			if (transformY > 0.0 && stripe > 0 && stripe < cb->frame->width && transformY < cb->rc->perp_dists[stripe])
				for(int y = drawStartY; y < drawEndY; y++)
				{
					double d = y - cb->frame->height / 2 + spriteHeight / 2;
					int texY = ((d * cb->sprite->height) / spriteHeight);
					int color = *((int *)(cb->sprite->image + cb->sprite->size_line * texY + texX * 4));
					if ((color & 0x00FFFFFF) != 0)
						*((int *)(cb->frame->image + cb->frame->size_line * y + stripe * 4)) = color;
				}
		}
	}
}

void			cb_draw_frame(t_cbdata *cb)
{
	cb_print_floor_and_ceilling(cb);
	cb_draw_walls(cb);
	cb_draw_sprites(cb);
}
