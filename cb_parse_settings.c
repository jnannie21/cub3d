/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parse_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:46:43 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/04 07:46:18 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"

static int		cb_read_resolution(t_cbdata *cb, char *line)
{
	int		sizex;
	int		sizey;

	line++;
	line += ft_strspn(line, " ");
	if (!ft_strchr("0123456789", *(line)) ||
		(cb->frame->width = ft_atoi(line)) <= 0)
		return (-1);
	line += ft_strspn(line, "0123456789");
	line += ft_strspn(line, " ");
	if (!ft_strchr("0123456789", *line) ||
		(cb->frame->height = ft_atoi(line)) <= 0)
		return (-1);
	line += ft_strspn(line, "0123456789");
	if (*line != '\0')
		return (-1);
	mlx_get_screen_size(cb->mlx_ptr, &sizex, &sizey);
	if (cb->frame->width > sizex)
		cb->frame->width = sizex;
	if (cb->frame->height > sizey)
		cb->frame->height = sizey;
	return (0);
}

static int		cb_read_texture(t_cbdata *cb, char *line)
{
	t_cbimage	*imgdata;

	if (!ft_memcmp(line, "NO", 2))
		imgdata = cb->no_texture;
	else if (!ft_memcmp(line, "SO", 2))
		imgdata = cb->so_texture;
	else if (!ft_memcmp(line, "WE", 2))
		imgdata = cb->we_texture;
	else if (!ft_memcmp(line, "EA", 2))
		imgdata = cb->ea_texture;
	else// if (!ft_memcmp(line, "S", 1))
		imgdata = cb->sprite;
//	else
//		return (cb_print_err(cbdata, CB_ERR_TEXTURE, -1));
	line += 2;
	line += ft_strspn(line, " ");
	if (!(imgdata->img_ptr = mlx_xpm_file_to_image(cb->mlx_ptr, line,
									&(imgdata->width), &(imgdata->height))))
		return (-1);
	imgdata->image = mlx_get_data_addr(imgdata->img_ptr,
		&(imgdata->bits_per_pixel), &(imgdata->size_line), &(imgdata->endian));
	return (0);
}

static int		cb_read_color(t_cbdata *cb, char *line)
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
	color = mlx_get_color_value(cb->mlx_ptr, color);
//	line += ft_strspn(line, " ");
	if (*temp_line == 'F')
		cb->floor_color = color;
	else// if (*temp_line == 'C')
		cb->ceilling_color = color;
	return (0);
}

void			cb_parse_settings_line(t_cbdata *cb, char *line)
{
	if (*line == '\0')
		return ;
	if (*line == 'R')
		if (cb_read_resolution(cb, line) == -1)
			cb_exit(cb, CB_ERR_RESOLUTION);//, -1);
	if (*line == 'F' || *line == 'C')
		if (cb_read_color(cb, line) == -1)
			cb_exit(cb, CB_ERR_COLOR);//, -1);
	if (ft_strchr("NSWE", *line))
		if (cb_read_texture(cb, line) == -1)
			cb_exit(cb, CB_ERR_TEXTURE);//, -1);
}
