/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:45:02 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/20 16:24:18 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

static int	cb_read_resolution(t_cbdata *cbdata, char *line)
{
	line++;
	line += ft_strspn(line, " ");
	if (!ft_strchr("0123456789", *line) ||
		(cbdata->win_width = ft_atoi(line)) < 0)
		return (-1);
	line += ft_strspn(line, "0123456789");
	line += ft_strspn(line, " ");
	if (!ft_strchr("0123456789", *line) ||
		(cbdata->win_height = ft_atoi(line)) < 0)
		return (-1);
	return (0);
}

static int	cb_read_texture(t_cbdata *cbdata, char *line)
{
	t_cbimage	*imgdata;

	if (!ft_memcmp(line, "NO", 2))
		imgdata = cbdata->no_texture;
	else if (!ft_memcmp(line, "SO", 2))
		imgdata = cbdata->so_texture;
	else if (!ft_memcmp(line, "WE", 2))
		imgdata = cbdata->we_texture;
	else if (!ft_memcmp(line, "EA", 2))
		imgdata = cbdata->ea_texture;
	else if (!ft_memcmp(line, "S", 1))
		imgdata = cbdata->sprite;
	else
		return (-1);
	line += 2;
	line += ft_strspn(line, " ");
	if (!(imgdata->img_ptr = mlx_xpm_file_to_image(cbdata->mlx_ptr, line,
									&(imgdata->width), &(imgdata->height))))
		return (-1);
	imgdata->image = mlx_get_data_addr(imgdata->img_ptr,
		&(imgdata->bits_per_pixel), &(imgdata->size_line), &(imgdata->endian));
	return (0);
}

static int	cb_read_color(t_cbdata *cbdata, char *line)
{
	int		channel;
	int		color;
	int		offset;

	offset = 0;
	color = 0;
	line++;
	while (offset <= 2)
	{
		line += ft_strspn(line, " ");
		if (!ft_strchr("0123456789", *line) ||
			(channel = ft_atoi(line)) < 0 ||
			channel > 255)
			return (-1);
		color = color | (channel << (offset * 8));
		line += ft_strspn(line, "0123456789");
		line = (*line == ',') ? line : line + 1;
		offset++;
	}
	color = mlx_get_color_value(cbdata->mlx_ptr, color);
	line++;
	if (*line == 'F')
		cbdata->floor_color = color;
	else if (*line == 'C')
		cbdata->ceilling_color = color;
	return (0);
}

static int	cb_read_map_line(t_cbdata *cbdata, char *line)
{
	int		lines_count;
	char	**temp;

	lines_count = 0;
	temp = cbdata->map;
	while (temp++)
		lines_count++;
	if (!(temp = ft_calloc(lines_count + 2, sizeof(char *))))
	{
		free(line);
		return (-1);
	}
	temp[lines_count] = line;
	while (lines_count--)
		temp[lines_count] = cbdata->map[lines_count];
	free(cbdata->map);
	cbdata->map = temp;
	return (0);
}

static int	cb_parse_settings_line(t_cbdata *cbdata, char *line)
{
	if (*line == '\0')
		return (0);
	else if (*line == 'R')
		return (cb_read_resolution(cbdata, line));
	else if (*line == 'F' || *line == 'C')
		return (cb_read_color(cbdata, line));
	else// if (ft_strchr("NSWE", *line))
		return (cb_read_texture(cbdata, line));
}

static int	cb_free_get_next_line_buf(int fd)
{
	get_next_line(fd, 0);
	return (-1);
}

int			cb_parse_map(t_cbdata *cbdata, char *filename)
{
	int		fd;
	char	*line;
	int		r;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	r = 1;
	while (r > 0 && (r = (get_next_line(fd, &line))) >= 0)
	{
		if (!cbdata->map && ft_strchr("NSWERFC", *line))
		{
			if (cb_parse_settings_line(cbdata, line) == -1)
				r = cb_free_get_next_line_buf(fd);
			free(line);
		}
		else if (cb_read_map_line(cbdata, line) == -1)
			r = cb_free_get_next_line_buf(fd);
	}
	close(fd);
	return (r);
}
