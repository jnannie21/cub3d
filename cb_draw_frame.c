/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_draw_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 21:49:44 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/03 04:40:52 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"
#include <math.h>

static void		cb_sort_sprites(t_cbdata *cbdata)
{
	int			i;
	int			j;
	int			found;
	t_sprite	temp;

	j = 0;
	found = 1;
	while (j < cbdata->sprites_num - 1 && found)
	{
		found = 0;
		i = 0;
		while (i < cbdata->sprites_num - 1 - j)
		{
			if (cbdata->sprites[i].dist < cbdata->sprites[i + 1].dist)
			{
				temp = cbdata->sprites[i];
				cbdata->sprites[i] = cbdata->sprites[i + 1];
				cbdata->sprites[i + 1] = temp;
				found = 1;
			}
			i++;
		}
		j++;
	}
}

void			cb_draw_line(t_cbdata *cbdata, int x, int line_start, int line_end, t_cbimage *texture, double texture_draw_start, int texX)
{
	int		y;
	int		int_frame_size_line;
	int		int_texture_size_line;
	int		texture_x;
	double	texture_step_y;
	int		tex_y;

	texture_step_y = (double)(texture->height - 2.0 * texture_draw_start) / (line_end - line_start + 1);
	int_frame_size_line = cbdata->frame->size_line / 4;
	int_texture_size_line = texture->size_line / 4;
	y = line_start;
	x = y * int_frame_size_line + x;
	tex_y = 0;
	while (y <= line_end)
	{
		texture_x = (int)(texture_draw_start + tex_y * texture_step_y) * int_texture_size_line + texX;
		if ((((int *)(texture->image))[texture_x] & 0x00FFFFFF) != 0)
			((int *)(cbdata->frame->image))[x] = ((int *)(texture->image))[texture_x];
		else
			((int *)(cbdata->frame->image))[x] = 0x000;
		x += int_frame_size_line;
		y++;
		tex_y++;
	}
}

void			cb_draw_frame(t_cbdata *cbdata)
{
	int		x;
	double	plane_scale;
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
	t_cbimage	*texture;
	double plane_step;
	double		texture_draw_start;
	double	ZBuffer[cbdata->frame->width]; //forbidden, change to dinamic buffer, or add to structure, why not

	x = 0;
	plane_step = 2.0 / cbdata->frame->width;
	plane_scale = -1;
	cb_print_floor_and_ceilling(cbdata);
		while (x < cbdata->frame->width)
		{
			hit = 0;
			plane_scale += plane_step;// * x - 1;
			ray_x = cbdata->dir_x + cbdata->plane_x * plane_scale;
			ray_y = cbdata->dir_y + cbdata->plane_y * plane_scale;
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
				if (cbdata->map[mapY][mapX] == '1')
					hit = 1;
			}

			if (side == 0)
				perpWallDist = (mapX - cbdata->pos_x + (1 - stepX) / 2) / ray_x;
			else
				perpWallDist = (mapY - cbdata->pos_y + (1 - stepY) / 2) / ray_y;

			lineHeight = (int)(cbdata->frame->height / perpWallDist);


			drawStart = (-lineHeight + cbdata->frame->height) / 2;

//			if (cbdata->map[mapY][mapX] == '2')
//				texture = cbdata->sprite;
//			else
//			{
				if (side == 0 && ray_x > 0)
					texture = cbdata->we_texture;
				else if (side == 0 && ray_x < 0)
					texture = cbdata->ea_texture;
				else if (side == 1 && ray_y > 0)
					texture = cbdata->no_texture;
				else if (side == 1 && ray_y < 0)
					texture = cbdata->so_texture;
//			}

			texture_draw_start = ((double)(texture->height) / lineHeight) * (drawStart < 0 ? -drawStart : 0);


			if (drawStart < 0)
				drawStart = 0;
			drawEnd = (lineHeight + cbdata->frame->height) / 2;
			if (drawEnd >= cbdata->frame->height)
				drawEnd = cbdata->frame->height - 1;

			double wallX; //where exactly the wall was hit
			if (side == 0) wallX = cbdata->pos_y + perpWallDist * ray_y;
			else           wallX = cbdata->pos_x + perpWallDist * ray_x;
			wallX -= floor((wallX));

			int texX = (int)(wallX * (double)(texture->width));
			if(side == 0 && ray_x < 0) texX = texture->width - texX - 1;
			if(side == 1 && ray_y > 0) texX = texture->width - texX - 1;

			cb_draw_line(cbdata, x, drawStart, drawEnd, texture, texture_draw_start, texX);

			x++;
			ZBuffer[x] = perpWallDist;
		}


			

				//SPRITE CASTING
				//sort sprites from far to close
			for (int i = 0; i < cbdata->sprites_num; i++)
			{
//				spriteOrder[i] = i;
				cbdata->sprites[i].dist = ((cbdata->pos_x - cbdata->sprites[i].x) * (cbdata->pos_x - cbdata->sprites[i].x) + (cbdata->pos_y - cbdata->sprites[i].y) * (cbdata->pos_y - cbdata->sprites[i].y)); //sqrt not taken, unneeded
			}
			cb_sort_sprites(cbdata);

			//after sorting the sprites, do the projection and draw them
			for (int i = 0; i < cbdata->sprites_num; i++)
			{
				//translate sprite position to relative to camera
				double spriteX = cbdata->sprites[i].x - cbdata->pos_x;
				double spriteY = cbdata->sprites[i].y - cbdata->pos_y;



				//transform sprite with the inverse camera matrix
				// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
				// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
				// [ planeY   dirY ]                                          [ -planeY  planeX ]


//				spriteX = -1;
	//			spriteY = -1;
/*
				double invDet = 1.0 / (cbdata->plane_x * cbdata->dir_y - cbdata->dir_x * cbdata->plane_y); //required for correct matrix multiplication

				double transformX = invDet * (cbdata->dir_y * spriteX - cbdata->dir_x * spriteY);
				double transformY = invDet * (-cbdata->plane_y * spriteX + cbdata->plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

					int spriteScreenX = cbdata->frame->width / 2;
					spriteScreenX = (int)((cbdata->frame->width / 2) * (1 + transformX / transformY));

*/
//				transformY = 0.004587;



				double perp_x = -cbdata->dir_x_perp;
				double perp_y = -cbdata->dir_y_perp;
double transformX = perp_x * spriteX + perp_y * spriteY;
double transformY = -perp_y * spriteX + perp_x * spriteY;
transformX = transformX / transformY / 0.66;

//				transformX = 1;
//				transformY = 2;

				int spriteScreenX = cbdata->frame->width / 2;
//				if (transformY != 0)

spriteScreenX = (int)((cbdata->frame->width / 2) * (1 - transformX));

				//calculate height of the sprite on screen
				int spriteHeight = 0;
//				if (transformY != 0)
					spriteHeight = abs((int)(cbdata->frame->height / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
				//calculate lowest and highest pixel to fill in current stripe
				int drawStartY = -spriteHeight / 2 + cbdata->frame->height / 2;
				if (drawStartY < 0) drawStartY = 0;
				int drawEndY = spriteHeight / 2 + cbdata->frame->height / 2;
				if (drawEndY >= cbdata->frame->height) drawEndY = cbdata->frame->height - 1;

				//calculate width of the sprite
				int spriteWidth = 0;
//				if (transformY != 0)
					spriteWidth = abs((int)(cbdata->frame->height / (transformY)));
				int drawStartX = -spriteWidth / 2 + spriteScreenX;
				if (drawStartX < 0) drawStartX = 0;
				int drawEndX = spriteWidth / 2 + spriteScreenX;
				if (drawEndX >= cbdata->frame->width) drawEndX = cbdata->frame->width - 1;

				//loop through every vertical stripe of the sprite on screen
				for (int stripe = drawStartX; stripe < drawEndX; stripe++)
				{
					int texX = (int)((stripe - (-spriteWidth / 2 + spriteScreenX)) * cbdata->sprite->width / spriteWidth);
					//the conditions in the if are:
					//1) it's in front of camera plane so you don't see things behind you
					//2) it's on the screen (left)
					//3) it's on the screen (right)
					//4) ZBuffer, with perpendicular distance
					if (transformY > 0.0 && stripe > 0 && stripe < cbdata->frame->width && transformY < ZBuffer[stripe])
						for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
						{
							double d = y - cbdata->frame->height / 2 + spriteHeight / 2; //256 and 128 factors to avoid floats
							int texY = ((d * cbdata->sprite->height) / spriteHeight);
							int color = *((int *)(cbdata->sprite->image + cbdata->sprite->size_line * texY + texX * 4)); //get current color from the texture
							if ((color & 0x00FFFFFF) != 0)
								*((int *)(cbdata->frame->image + cbdata->frame->size_line * y + stripe * 4)) = color; //paint pixel if it isn't black, black is the invisible color
						}
				}
			}
			
}
