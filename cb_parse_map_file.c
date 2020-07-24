/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parse_map_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:45:02 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/24 12:53:29 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"
//#include <stdio.h>

static int		cb_read_map_line(t_cbdata *cbdata, char *line)
{
	size_t		lines_count;
	char		**temp;

	lines_count = 0;
	temp = cbdata->map;
	while (temp && *temp++)
		lines_count++;
	if (!(temp = ft_calloc(lines_count + 2, sizeof(char *))))
		return (-1);
	temp[lines_count] = line;
	while (lines_count--)
		temp[lines_count] = cbdata->map[lines_count];
	free(cbdata->map);
	cbdata->map = temp;
	return (0);
}

int				cb_parse_map_file(t_cbdata *cbdata, char *filename)
{
	int		r;
	char	*temp;

	errno = 0;
	if (!(temp = ft_strnstr(filename, ".cub", ft_strlen(filename))) ||
		*(temp + 4) != '\0' ||
		(cbdata->fd = open(filename, O_RDONLY)) == -1)
		cb_exit(cbdata, CB_ERR_READ_FILE);//, -1);
	r = 1;
	while (r > 0 && (r = (get_next_line(cbdata->fd, &(cbdata->line)))) >= 0)
	{
		errno = 0;
		if (!cbdata->map && ft_strchr("NSWERFC", *(cbdata->line)))
		{
			cb_parse_settings_line(cbdata, cbdata->line);
			free(cbdata->line);
//			cbdata->line = 0;
		}
		else if (cb_read_map_line(cbdata, cbdata->line) == -1)
				r = -1;
		cbdata->line = 0;
	}
	if (r == -1)
		cb_exit(cbdata, CB_ERR_READ_FILE);//, -1);
	if (!cbdata->map ||
		!cbdata->no_texture->img_ptr || !cbdata->so_texture->img_ptr ||
		!cbdata->we_texture->img_ptr || !cbdata->ea_texture->img_ptr ||
		!cbdata->sprite->img_ptr || cbdata->floor_color == 0x80000000 ||
		cbdata->ceilling_color == 0x80000000)
			cb_exit(cbdata, CB_ERR_MAP_FILE);//, -1);
	if (cb_parse_map(cbdata) == -1)
		cb_exit(cbdata, CB_ERR_MAP);//, -1);
	close(cbdata->fd);
	cbdata->fd = -1;
	return (0);
}
