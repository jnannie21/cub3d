/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:43:17 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/31 17:35:48 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"
#include <math.h>

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

void			cb_rotate_vectors(t_cbdata *cbdata, double angle)
{
	double	temp_x;
	double	temp_y;
	static double	cosine;
	static double	sine;
	static double	last_angle;

	if ((sine == 0 && cosine == 0) || last_angle != angle)
	{
		cosine = cos(angle);
		sine = sin(angle);
	}
	last_angle = angle;
	temp_x = cbdata->dir_x;
	temp_y = cbdata->dir_y;
	cbdata->dir_x = temp_x * cosine - temp_y * sine;
	cbdata->dir_y = temp_x * sine + temp_y * cosine;
	temp_x = cbdata->dir_x_perp;
	temp_y = cbdata->dir_y_perp;
	cbdata->dir_x_perp = temp_x * cosine - temp_y * sine;
	cbdata->dir_y_perp = temp_x * sine + temp_y * cosine;
	temp_x = cbdata->plane_x;
	temp_y = cbdata->plane_y;
	cbdata->plane_x = temp_x * cosine - temp_y * sine;
	cbdata->plane_y = temp_x * sine + temp_y * cosine;
}

static void		cb_set_start_position(t_cbdata *cbdata, size_t x, size_t y, char pos)
{
	cbdata->pos_x = (double)x + 0.5;
	cbdata->pos_y = (double)y + 0.5;
	cbdata->dir_x = 1;
	cbdata->dir_y = 0;
	cbdata->dir_x_perp = 0;
	cbdata->dir_y_perp = 1;
	cbdata->plane_x = 0;
	cbdata->plane_y = 0.66;
	if (pos == 'N')
		cb_rotate_vectors(cbdata, (double)(M_PI + M_PI / 2));
	else if (pos == 'S')
		cb_rotate_vectors(cbdata, (double)(M_PI / 2));
	else if (pos == 'W')
		cb_rotate_vectors(cbdata, (double)M_PI);
	else// if (pos == 'E')
		cb_rotate_vectors(cbdata, (double)0);
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

static int		cb_check_if_map_closed(t_cbdata *cbdata)
{
	char		**temp_map;
	int			r;

	if (!(temp_map = cb_dup_map(cbdata->map)))
		return (-1);
//	temp_map[(int)(cbdata->pos_y)][(int)(cbdata->pos_x)] = CB_WAS_HERE;
	r = 0;
	if (cb_search_way_out(temp_map, cbdata->pos_x, cbdata->pos_y))
		r = -1;
	cb_print_map(temp_map);
	cb_free_map(temp_map);
	return (r);
}

static int		cb_count_sprites(t_cbdata *cbdata)
{
	int		x;
	int		y;
	int		count;

	x = 0;
	y = 0;
	count = 0;
	while (cbdata->map[y])
	{
		x = 0;
		while (cbdata->map[y][x])
		{
			if (cbdata->map[y][x] == '2')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static int		cb_search_sprites(t_cbdata *cbdata)
{
	int			x;
	int			y;
	t_sprite	*sprites;

	x = 0;
	y = 0;
	cbdata->sprites_num = cb_count_sprites(cbdata);
	if (!(cbdata->sprites = ft_calloc(cbdata->sprites_num, sizeof(t_sprite))))
		return (-1);
	sprites = cbdata->sprites;
	while (cbdata->map[y])
	{
		x = 0;
		while (cbdata->map[y][x])
		{
			if (cbdata->map[y][x] == '2')
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

int				cb_parse_map(t_cbdata *cbdata)
{
	char		*line;
	size_t		x;
	size_t		y;
	char		pos;

	y = 0;
	while ((line = cbdata->map[y]))
	{
		if (*(line + ft_strspn(line, CB_VALID_CHARS)) != '\0' || *line == '\0')
			return (-1);
		x = ft_strcspn(line, "NSWE");
		pos = *(line + x);
		if (pos)
		{
			*(line + x) = '0';
			if (!y || !x || cbdata->pos_x ||
				*(line + ft_strcspn(line, "NSWE")))
				return (-1);
			cb_set_start_position(cbdata, x, y, pos);
		}
		y++;
	}
	if (!(size_t)(cbdata->pos_x) ||
		cb_check_if_map_closed(cbdata) == -1 ||
		cb_search_sprites(cbdata) == -1)
		return (-1);
	return (0);
}
