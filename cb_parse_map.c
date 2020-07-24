/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:43:17 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/24 12:48:46 by jnannie          ###   ########.fr       */
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

static void		cb_set_start_position(t_cbdata *cbdata, size_t x, size_t y, char dir)
{
	cbdata->pos_x = (double)x + 0.5;
	cbdata->pos_y = (double)y + 0.5;
	if (dir == 'N')
	{
		cbdata->dir_x = 0;
		cbdata->dir_y = 1;
	}
	else if (dir == 'S')
	{
		cbdata->dir_x = 0;
		cbdata->dir_y = -1;
	}
	else if (dir == 'W')
	{
		cbdata->dir_x = -1;
		cbdata->dir_y = 0;
	}
	else// if (dir == 'E')
	{
		cbdata->dir_x = 1;
		cbdata->dir_y = 0;
	}
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

int				cb_parse_map(t_cbdata *cbdata)
{
	char		*line;
	size_t		x;
	size_t		y;

	y = 0;
	while ((line = cbdata->map[y]))
	{
		if (*(line + ft_strspn(line, CB_VALID_CHARS)) != '\0' || *line == '\0')
			return (-1);
		x = ft_strcspn(line, "NSWE");
		if (*(line + x))
		{
			if (!y || !x || cbdata->pos_x ||
				*(line + x + 1 + ft_strcspn(line + x + 1, "NSWE")))
				return (-1);
			cb_set_start_position(cbdata, x, y, *(line + x));
		}
		y++;
	}
	if (!(size_t)(cbdata->pos_x) ||
		cb_check_if_map_closed(cbdata) == -1)
		return (-1);
	return (0);
}
