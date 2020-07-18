/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:45:02 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/18 17:30:55 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"
#include <fcntl.h>
#include <unistd.h>

static int	cb_parse_line(t_cbdata *cbdata, char *line)
{
	if (!ft_memcmp(line, "R", 1))
		cb_read_resolution(cbdata, line);
	else if (!ft_memcmp(line, "NO", 2))
		cb_read_north_texture(bdata, line)
	else if (!ft_memcmp(line, "R", 1))
	else if (!ft_memcmp(line, "R", 1))
	else if (!ft_memcmp(line, "R", 1))
	else if (!ft_memcmp(line, "R", 1))
	else if (!ft_memcmp(line, "R", 1))
	else if (!ft_memcmp(line, "R", 1))
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
