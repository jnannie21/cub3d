/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parse_map_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:45:02 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/23 23:59:40 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"
//#include <stdio.h>

#define CB_WAS_HERE -1

void			cb_print_map(char **map)
{
	while (*map)
	{
		write(1, *map, ft_strlen(*map));
		write(1, "\n", 1);
		map++;
	}
}

static int		cb_read_resolution(t_cbdata *cbdata, char *line)
{
	line++;
	line += ft_strspn(line, " ");
	if (!ft_strchr("0123456789", *(line)) ||
		(cbdata->win_width = ft_atoi(line)) <= 0)
		return (-1);
	line += ft_strspn(line, "0123456789");
	line += ft_strspn(line, " ");
	if (!ft_strchr("0123456789", *line) ||
		(cbdata->win_height = ft_atoi(line)) <= 0)
		return (-1);
	line += ft_strspn(line, "0123456789");
	if (*line != '\0')
		return (-1);
	return (0);
}

static int		cb_read_texture(t_cbdata *cbdata, char *line)
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
	else// if (!ft_memcmp(line, "S", 1))
		imgdata = cbdata->sprite;
//	else
//		return (cb_print_err(cbdata, CB_ERR_TEXTURE, -1));
	line += 2;
	line += ft_strspn(line, " ");
	if (!(imgdata->img_ptr = mlx_xpm_file_to_image(cbdata->mlx_ptr, line,
									&(imgdata->width), &(imgdata->height))))
		return (-1);
	imgdata->image = mlx_get_data_addr(imgdata->img_ptr,
		&(imgdata->bits_per_pixel), &(imgdata->size_line), &(imgdata->endian));
	return (0);
}

static int		cb_read_color(t_cbdata *cbdata, char *line)
{
	int		channel;
	int		color;
	int		offset;
	char	*temp_line;

	offset = 0;
	color = 0;
	temp_line = line;
	line++;
	while (offset <= 2)
	{
		line += ft_strspn(line, " ");
		if (!ft_strchr("0123456789", *line) ||
			(channel = ft_atoi(line)) < 0 ||
			channel > 255)
			return (-1);
		color = (color << 8) | channel;
		line += ft_strspn(line, "0123456789");
		if (offset >= 2 && *line != '\0')
			return (-1);
		line += ft_strspn(line, " ");
//		if (*line != ',' && offset < 2)
//			return (-1);
		line = (*line == ',') ? line + 1 : line;
		offset++;
	}
	color = mlx_get_color_value(cbdata->mlx_ptr, color);
//	line += ft_strspn(line, " ");
	if (*temp_line == 'F')
		cbdata->floor_color = color;
	else// if (*temp_line == 'C')
		cbdata->ceilling_color = color;
	return (0);
}

static void		cb_read_map_line(t_cbdata *cbdata, char *line)
{
	size_t		lines_count;
	char		**temp;

	lines_count = 0;
	temp = cbdata->map;
	while (temp && *temp++)
		lines_count++;
	if (!(temp = ft_calloc(lines_count + 2, sizeof(char *))))
		cb_exit(cbdata, CB_ERR_MAP, -1);
	temp[lines_count] = line;
	while (lines_count--)
		temp[lines_count] = cbdata->map[lines_count];
	free(cbdata->map);
	cbdata->map = temp;
}

static void		cb_parse_settings_line(t_cbdata *cbdata, char *line)
{
	if (*line == '\0')
		return ;
	if (*line == 'R')
		if (cb_read_resolution(cbdata, line) == -1)
			cb_exit(cbdata, CB_ERR_RESOLUTION, -1);
	if (*line == 'F' || *line == 'C')
		if (cb_read_color(cbdata, line) == -1)
			cb_exit(cbdata, CB_ERR_COLOR, -1);
	if (ft_strchr("NSWE", *line))
		if (cb_read_texture(cbdata, line) == -1)
			cb_exit(cbdata, CB_ERR_TEXTURE, -1);
}

int			cb_free_get_next_line_buf(int fd)
{
	get_next_line(fd, 0);
	return (-1);
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

static void		cb_parse_map(t_cbdata *cbdata)
{
	char		*line;
	size_t		x;
	size_t		y;

	y = 0;
	while ((line = cbdata->map[y]))
	{
		if (*(line + ft_strspn(line, CB_VALID_CHARS)) != '\0' || *line == '\0')
			cb_exit(cbdata, CB_ERR_MAP, -1);
		x = ft_strcspn(line, "NSWE");
		if (*(line + x))
		{
			if (!y || !x || cbdata->pos_x ||
				*(line + x + 1 + ft_strcspn(line + x + 1, "NSWE")))
				cb_exit(cbdata, CB_ERR_MAP, -1);
			cb_set_start_position(cbdata, x, y, *(line + x));
		}
		y++;
	}
	if (!(size_t)(cbdata->pos_x) ||
		cb_check_if_map_closed(cbdata) == -1)
		cb_exit(cbdata, CB_ERR_MAP, -1);
}

int				cb_parse_map_file(t_cbdata *cbdata, char *filename)
{
	int		r;

	if ((cbdata->fd = open(filename, O_RDONLY)) == -1)
		cb_exit(cbdata, CB_ERR_FILE, -1);
	r = 1;
	while (r > 0 && (r = (get_next_line(cbdata->fd, &(cbdata->line)))) >= 0)
	{
		errno = 0;
		if (!cbdata->map && ft_strchr("NSWERFC", *(cbdata->line)))
		{
			cb_parse_settings_line(cbdata, cbdata->line);
			free(cbdata->line);
			cbdata->line = 0;
		}
		else
		{
			cb_read_map_line(cbdata, cbdata->line);
			cbdata->line = 0;
		}
	}
	if (r == -1 || !cbdata->map ||
		!cbdata->no_texture->img_ptr || !cbdata->so_texture->img_ptr ||
		!cbdata->we_texture->img_ptr || !cbdata->ea_texture->img_ptr ||
		!cbdata->sprite->img_ptr || cbdata->floor_color == 0x80000000 ||
		cbdata->ceilling_color == 0x80000000)
			cb_exit(cbdata, CB_ERR_FILE, -1);
	cb_parse_map(cbdata);
//	r = cb_parse_map(cbdata);
	close(cbdata->fd);
//	if (r == -1)
//		return (cb_print_err(cbdata, CB_ERR_FILE, -1));
	return (0);
}
