/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:43:17 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/05 22:25:17 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cb_cub3d.h"

static void		cb_set_start_position(t_cbdata *cb, size_t x,
										size_t y, char pos)
{
	cb->pos_x = (double)x + 0.5;
	cb->pos_y = (double)y + 0.5;
	cb->dir_x = 1;
	cb->dir_y = 0;
	cb->dir_x_perp = 0;
	cb->dir_y_perp = 1;
	cb->plane_x = 0;
	cb->plane_y = 0.66;
	if (pos == 'N')
		cb_rotate_vectors(cb, (double)(M_PI + M_PI / 2));
	else if (pos == 'S')
		cb_rotate_vectors(cb, (double)(M_PI / 2));
	else if (pos == 'W')
		cb_rotate_vectors(cb, (double)M_PI);
	else
		cb_rotate_vectors(cb, (double)0);
}

static size_t	cb_count_sprites(t_cbdata *cb)
{
	size_t		x;
	size_t		y;
	size_t		count;

	x = 0;
	y = 0;
	count = 0;
	while (cb->map[y])
	{
		x = 0;
		while (cb->map[y][x])
		{
			if (cb->map[y][x] == '2')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static int		cb_search_sprites(t_cbdata *cb)
{
	size_t		x;
	size_t		y;
	t_sprite	*sprites;

	y = 0;
	cb->sprites_num = cb_count_sprites(cb);
	if (!(cb->sprites = ft_calloc(cb->sprites_num, sizeof(t_sprite))))
		return (-1);
	sprites = cb->sprites;
	while (cb->map[y])
	{
		x = 0;
		while (cb->map[y][x])
		{
			if (cb->map[y][x] == '2')
			{
				sprites->x = x + 0.5;
				sprites->y = y + 0.5;
				sprites++;
			}
			x++;
		}
		y++;
	}
	return (0);
}

int				cb_parse_map(t_cbdata *cb)
{
	char		*line;
	size_t		x;
	size_t		y;

	y = 0;
	while ((line = cb->map[y]))
	{
		if (*(line + ft_strspn(line, CB_VALID_CHARS)) != '\0' || *line == '\0')
			return (-1);
		x = ft_strcspn(line, "NSWE");
		if (*(line + x))
		{
			if (!y || !x || cb->pos_x
				|| *(line + x + 1 + ft_strcspn(line + x + 1, "NSWE")))
				return (-1);
			cb_set_start_position(cb, x, y, *(line + x));
		}
		y++;
	}
	if (!(size_t)(cb->pos_x)
		|| cb_check_walls(cb) == -1
		|| cb_search_sprites(cb) == -1)
		return (-1);
	return (0);
}
