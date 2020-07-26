/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_draw_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 21:49:44 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/26 19:42:46 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"

#include <math.h>

void		cb_verLine(t_cbdata *cbdata, int x, int drawStart, int drawEnd, int color)
{
	int		y;

	//color = 0xF0FFF0;
	y = drawStart;
	while (y <= drawEnd)
	{
		((int *)(cbdata->frame->image))[y * cbdata->frame->size_line / 4 + x] = color;
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
	int	h;
	int lineHeight;
	int drawStart;
	int drawEnd;
	int color;

	h = cbdata->frame->height;
	x = 0;
		while (x < cbdata->frame->width)
		{
			hit = 0;
			plane_projection = 2.0 * x / (double)(cbdata->frame->width) - 1;
			ray_x = cbdata->dir_x + cbdata->plane_x * plane_projection;
			ray_y = cbdata->dir_y + cbdata->plane_y * plane_projection;
			mapX = (int)(cbdata->pos_x);
			mapY = (int)(cbdata->pos_y);
			deltaDistX = fabs(1 / ray_x);
			deltaDistY = fabs(1 / ray_y);

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
				//jump to next map square, OR in x-direction, OR in y-direction
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
				//Check if ray has hit a wall
				if (cbdata->map[mapY][mapX] > '0')// || cbdata->map[mapX][mapY] == ' ')
					hit = 1;
			}

			if (side == 0)
				perpWallDist = (mapX - cbdata->pos_x + (1 - stepX) / 2) / ray_x;
			else
				perpWallDist = (mapY - cbdata->pos_y + (1 - stepY) / 2) / ray_y;

			//Calculate height of line to draw on screen
			lineHeight = (int)(h / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			drawStart = -lineHeight / 2 + h / 2;
			if (drawStart < 0)
				drawStart = 0;
			drawEnd = lineHeight / 2 + h / 2;
			if (drawEnd >= h)
				drawEnd = h - 1;

			//choose wall color
			switch (cbdata->map[mapY][mapX])
			{
				case '1': color = 0xFFFF * 254 + 0xFF * 0 + 0;  break; //red
				case '2': color = 0xFFFF * 0 + 0xFF * 254 + 0;  break; //green
//				case 3:  color = 0xFFFF * 0 + 0xFF * 0 + 254;   break; //blue
//				case 4:  color = 0xFFFF * 254 + 0xFF * 254 + 254;  break; //white
				default: color = 0xFFFF * 254 + 0xFF * 254 + 0; break; //yellow
			}

			//give x and y sides different brightness
			if (side == 1)
					color = color / 2;

			//draw the pixels of the stripe as a vertical line
			cb_verLine(cbdata, x, drawStart, drawEnd, color);

			x++;
		}
}
