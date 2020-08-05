/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_check_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 22:23:29 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/05 22:24:20 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cb_cub3d.h"

#define CB_WAS_HERE 'x'

static char		**cb_dup_map(char **map)
{
	char		**temp_map;
	size_t		lines;

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

int				cb_check_walls(t_cbdata *cb)
{
	char		**temp_map;
	int			r;

	if (!(temp_map = cb_dup_map(cb->map)))
		return (-1);
	r = 0;
	if (cb_search_way_out(temp_map, cb->pos_x, cb->pos_y))
		r = -1;
	cb_print_map(temp_map);
	cb_free_map(temp_map);
	return (r);
}
