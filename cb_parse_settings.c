/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parse_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:46:43 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/24 12:53:21 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"

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

void			cb_parse_settings_line(t_cbdata *cbdata, char *line)
{
	if (*line == '\0')
		return ;
	if (*line == 'R')
		if (cb_read_resolution(cbdata, line) == -1)
			cb_exit(cbdata, CB_ERR_RESOLUTION);//, -1);
	if (*line == 'F' || *line == 'C')
		if (cb_read_color(cbdata, line) == -1)
			cb_exit(cbdata, CB_ERR_COLOR);//, -1);
	if (ft_strchr("NSWE", *line))
		if (cb_read_texture(cbdata, line) == -1)
			cb_exit(cbdata, CB_ERR_TEXTURE);//, -1);
}
