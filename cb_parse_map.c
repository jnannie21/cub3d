/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:43:17 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/05 10:33:49 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"

#define CB_WAS_HERE -1

static void		cb_print_map(char **map)
{
	while (*map)
	{
		write(1, *map, ft_strlen(*map));
		write(1, "\n", 1);
		map++;
	}
}

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
	else// if (pos == 'E')
		cb_rotate_vectors(cb, (double)0);
}

static char		**cb_dup_map(char **map)
{
	char	**temp_map;
	size_t	lines;

	lines = 0;
	temp_map = map;
	while (*temp_map++)
		lines++;
	if (!(temp_map = ft_calloc(lines + 1, sizeof(char *))))
		return (0);
	while (lines--)
		if (!(temp_map[lines] = ft_strdup(map[lines])))
		{
			cb_free_map(temp_map);
			return (0);
		}
	return (temp_map);
}

static int		cb_search_way_out(char **temp_map, size_t x, size_t y)
{
	if (temp_map[y] == 0 || x >= ft_strlen(temp_map[y]))
		return (1);
	if (temp_map[y][x] == '1' || temp_map[y][x] == CB_WAS_HERE)
		return (0);
	if (x == 0 || y == 0 || temp_map[y][x] == ' ' || temp_map[y][x] == '\0')
		return (1);
	temp_map[y][x] = CB_WAS_HERE;
	if (cb_search_way_out(temp_map, x, y + 1) == 1)
		return (1);
	if (cb_search_way_out(temp_map, x + 1, y) == 1)
		return (1);
	if (cb_search_way_out(temp_map, x, y - 1) == 1)
		return (1);
	if (cb_search_way_out(temp_map, x - 1, y) == 1)
		return (1);
	return (0);
}

static int		cb_check_if_map_closed(t_cbdata *cb)
{
	char		**temp_map;
	int			r;

	if (!(temp_map = cb_dup_map(cb->map)))
		return (-1);
//	temp_map[(int)(cbdata->pos_y)][(int)(cbdata->pos_x)] = CB_WAS_HERE;
	r = 0;
	if (cb_search_way_out(temp_map, cb->pos_x, cb->pos_y))
		r = -1;
	cb_print_map(temp_map);
	cb_free_map(temp_map);
	return (r);
}

static size_t		cb_count_sprites(t_cbdata *cb)
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
	size_t			x;
	size_t			y;
	t_sprite		*sprites;

//	x = 0;
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
	char		pos;

	y = 0;
	while ((line = cb->map[y]))
	{
		if (*(line + ft_strspn(line, CB_VALID_CHARS)) != '\0' || *line == '\0')
			return (-1);
		x = ft_strcspn(line, "NSWE");
		pos = *(line + x);
		if (pos)
		{
			*(line + x) = '0';
			if (!y || !x || cb->pos_x ||
				*(line + ft_strcspn(line, "NSWE")))
				return (-1);
			cb_set_start_position(cb, x, y, pos);
		}
		y++;
	}
	if (!(size_t)(cb->pos_x) ||
		cb_check_if_map_closed(cb) == -1 ||
		cb_search_sprites(cb) == -1)
		return (-1);
	return (0);
}
