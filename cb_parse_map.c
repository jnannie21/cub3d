/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:45:02 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/19 05:54:35 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"
#include <fcntl.h>
#include <unistd.h>

static int	cb_read_resolution(&(cbdata->resolution), line)
{

}

static int	cb_read_texture(&(cbdata->south_texture), line)
{

}

static int	cb_read_color(&(cbdata->floor_color), line)
{

}

static int	cb_read_map_line(cbdata, line)
{

}

static int	cb_parse_line(t_cbdata *cbdata, char *line)
{
	if (!ft_memcmp(line, "R", 1))
		return (cb_read_resolution(&(cbdata->resolution), line));
	else if (!ft_memcmp(line, "NO", 2))
		return (cb_read_texture(&(cbdata->north_texture), line));
	else if (!ft_memcmp(line, "SO", 1))
		return (cb_read_texture(&(cbdata->south_texture), line));
	else if (!ft_memcmp(line, "WE", 1))
		return (cb_read_texture(&(cbdata->west_texture), line));
	else if (!ft_memcmp(line, "EA", 1))
		return (cb_read_texture(&(cbdata->east_texture), line));
	else if (!ft_memcmp(line, "S", 1))
		return (cb_read_texture(&(cbdata->sprite_texture), line));
	else if (!ft_memcmp(line, "F", 1))
		return (cb_read_color(&(cbdata->floor_color), line));
	else if (!ft_memcmp(line, "C", 1))
		return (cb_read_color(&(cbdata->ceilling_color), line));
	else if (*line != '\n')
		return (cb_read_map_line(cbdata, line));
	return (0);
}

int			cb_parse_map(t_cbdata *cbdata, char *filename)
{
	int		fd;
	char	*line;
	int		r;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	while ((r = (get_next_line(fd, &line))) > 0)
		if (cb_parse_line(cbdata, line) == -1) //parse and free line after read, even if error
			{
				close(fd);
				return (get_next_line(fd, 0)); // pass 0 to free buffer and return -1 if current line is incorrect
			}
	close(fd);
	return ((r == -1) ? r : cb_parse_line(cbdata, line));
}
