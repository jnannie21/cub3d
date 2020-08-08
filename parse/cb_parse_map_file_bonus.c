/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parse_map_file_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:45:02 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/08 13:16:13 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cb_cub3d_bonus.h"

static int		cb_read_map_line(t_cbdata *cb, char *line)
{
	size_t		lines_count;
	char		**temp;

	lines_count = 0;
	temp = cb->map;
	while (temp && *temp++)
		lines_count++;
	if (!(temp = ft_calloc(lines_count + 2, sizeof(char *))))
	{
		free(line);
		return (-1);
	}
	temp[lines_count] = line;
	while (lines_count--)
		temp[lines_count] = cb->map[lines_count];
	free(cb->map);
	cb->map = temp;
	return (0);
}

static int		cb_open_map_file(t_cbdata *cb, char *filename)
{
	char	*temp;

	errno = 0;
	if (!(temp = ft_strrchr(filename, '.'))
		|| ft_memcmp(temp, ".cub", 5)
		|| (cb->map_fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	return (0);
}

static int		cb_check_settings(t_cbdata *cb)
{
	if (!cb->map
		|| !cb->no_texture->img_ptr || !cb->so_texture->img_ptr
		|| !cb->we_texture->img_ptr || !cb->ea_texture->img_ptr
		|| !cb->sprite->img_ptr || cb->floor_color == 0x80000000
		|| cb->ceilling_color == 0x80000000 || !cb->bonus_sprite->img_ptr)
		return (-1);
	return (0);
}

int				cb_parse_map_file(t_cbdata *cb, char *filename)
{
	int		r;

	if (cb_open_map_file(cb, filename) == -1)
		cb_exit(cb, CB_ERR_READ_FILE);
	r = 1;
	while (r > 0 && (r = (get_next_line(cb->map_fd, &(cb->line)))) >= 0)
	{
		errno = 0;
		if (!cb->map && ft_strchr("NSWERFCB", *(cb->line)))
		{
			cb_parse_settings_line(cb, cb->line);
			free(cb->line);
		}
		else if (cb_read_map_line(cb, cb->line) == -1)
			r = -1;
		cb->line = 0;
	}
	if (r == -1)
		cb_exit(cb, CB_ERR_READ_FILE);
	if (cb_check_settings(cb) == -1)
		cb_exit(cb, CB_ERR_MAP_FILE);
	if (cb_parse_map(cb) == -1)
		cb_exit(cb, CB_ERR_MAP);
	return (0);
}
