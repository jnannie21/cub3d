/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parse_settings_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:46:43 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/07 13:01:05 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cb_cub3d_bonus.h"

static int		cb_read_resolution(t_cbdata *cb, char *line)
{
	int			sizex;
	int			sizey;

	if (cb->frame->width)
		return (-1);
	line++;
	line += ft_strspn(line, " ");
	if (!ft_isdigit(*line)
		|| (cb->frame->width = ft_atoi(line)) <= 0)
		return (-1);
	line += ft_strspn(line, "0123456789");
	line += ft_strspn(line, " ");
	if (!ft_isdigit(*line)
		|| (cb->frame->height = ft_atoi(line)) <= 0)
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

	if (!ft_memcmp(line, "NO ", 3) && !(cb->no_texture->img_ptr))
		imgdata = cb->no_texture;
	else if (!ft_memcmp(line, "SO ", 3) && !(cb->so_texture->img_ptr))
		imgdata = cb->so_texture;
	else if (!ft_memcmp(line, "WE ", 3) && !(cb->we_texture->img_ptr))
		imgdata = cb->we_texture;
	else if (!ft_memcmp(line, "EA ", 3) && !(cb->ea_texture->img_ptr))
		imgdata = cb->ea_texture;
	else if (!ft_memcmp(line, "BS ", 3) && !(cb->bonus_sprite->img_ptr))
		imgdata = cb->bonus_sprite;
	else if (!ft_memcmp(line, "S ", 2) && !(cb->sprite->img_ptr))
		imgdata = cb->sprite;
	else
		return (-1);
	line += 2;
	line += ft_strspn(line, " ");
	if (!(imgdata->img_ptr = mlx_xpm_file_to_image(cb->mlx_ptr, line,
									&(imgdata->width), &(imgdata->height))))
		return (-1);
	imgdata->image = mlx_get_data_addr(imgdata->img_ptr,
		&(imgdata->bits_per_pixel), &(imgdata->size_line), &(imgdata->endian));
	return (0);
}

void			cb_parse_settings_line(t_cbdata *cb, char *line)
{
	if (*line == '\0')
		return ;
	if (*line == 'R')
		if (cb_read_resolution(cb, line) == -1)
			cb_exit(cb, CB_ERR_RESOLUTION);
	if (*line == 'F' || *line == 'C')
		if (cb_read_color(cb, line) == -1)
			cb_exit(cb, CB_ERR_COLOR);
	if (ft_strchr("NSWEB", *line))
		if (cb_read_texture(cb, line) == -1)
			cb_exit(cb, CB_ERR_TEXTURE);
}
