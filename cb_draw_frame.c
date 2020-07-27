/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_draw_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 21:49:44 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/27 18:03:28 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"

#include <math.h>

void		cb_draw_line(t_cbdata *cbdata, int x, int line_start, int line_end, int color)
{
	int		y;
	int		int_size_line;

	int_size_line = cbdata->frame->size_line / 4;
	y = line_start;
	x = y * int_size_line + x;
	while (y <= line_end)
	{
		((int *)(cbdata->frame->image))[x] = color;
		x += int_size_line;
		y++;
	}
}

void		cb_draw_frame(t_cbdata *cbdata)
{
	int		x;
	double	plane_projection;
	double	ray_x;
	double	ray_y;

	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;

	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int hit; 
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	int color;
	double plane_step;

	x = 0;
	plane_step = 2.0 / cbdata->frame->width;
	plane_projection = -1;
	cb_print_floor_and_ceilling(cbdata);
		while (x < cbdata->frame->width)
		{
			hit = 0;
			plane_projection += plane_step;// * x - 1;
			ray_x = cbdata->dir_x + cbdata->plane_x * plane_projection;
			ray_y = cbdata->dir_y + cbdata->plane_y * plane_projection;
			mapX = (int)(cbdata->pos_x);
			mapY = (int)(cbdata->pos_y);
			deltaDistX = ray_x < 0 ? -1 / ray_x : 1 / ray_x;//fabs(1 / ray_x);
			deltaDistY = ray_y < 0 ? -1 / ray_y : 1 / ray_y;//fabs(1 / ray_y);

			if (ray_x < 0)
			{
				stepX = -1;
				sideDistX = (cbdata->pos_x - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - cbdata->pos_x) * deltaDistX;
			}
			if (ray_y < 0)
			{
				stepY = -1;
				sideDistY = (cbdata->pos_y - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - cbdata->pos_y) * deltaDistY;
			}
			while (hit == 0)
			{
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				if (cbdata->map[mapY][mapX] > '0')
					hit = 1;
			}

			if (side == 0)
				perpWallDist = (mapX - cbdata->pos_x + (1 - stepX) / 2) / ray_x;
			else
				perpWallDist = (mapY - cbdata->pos_y + (1 - stepY) / 2) / ray_y;

			lineHeight = (int)(cbdata->frame->height / perpWallDist);

			drawStart = (-lineHeight + cbdata->frame->height) / 2;
			if (drawStart < 0)
				drawStart = 0;
			drawEnd = (lineHeight + cbdata->frame->height) / 2;
			if (drawEnd >= cbdata->frame->height)
				drawEnd = cbdata->frame->height - 1;

			switch (cbdata->map[mapY][mapX])
			{
				case '1': color = 0xFFFF * 254 + 0xFF * 0 + 0;  break; //red
				case '2': color = 0xFFFF * 0 + 0xFF * 254 + 0;  break; //green
				default: color = 0xFFFF * 254 + 0xFF * 254 + 0; break; //yellow
			}

			//give x and y sides different brightness
			if (side == 1)
					color = color / 2;

			cb_draw_line(cbdata, x, drawStart, drawEnd, color);

			x++;
		}
}
