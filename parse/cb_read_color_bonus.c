/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_read_color_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 12:57:25 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/12 13:34:42 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cb_cub3d_bonus.h"

static int		cb_read_channel(int color, char *line)
{
	int			channel;

	if (!ft_isdigit(*line)
		|| (channel = ft_atoi(line)) < 0
		|| channel > 255)
		return (-1);
	color = (color << 8) | channel;
	return (color);
}

static int		cb_set_color(t_cbdata *cb, int color, char set)
{
	if (set == 'F' && cb->floor_color == 0x80000000)
		cb->floor_color = color;
	else if (set == 'C' && cb->ceilling_color == 0x80000000)
		cb->ceilling_color = color;
	else
		return (-1);
	return (0);
}

int				cb_read_color(t_cbdata *cb, char *line)
{
	int			color;
	int			offset;
	char		*temp_line;

	color = 0;
	offset = -1;
	temp_line = line;
	line++;
	while (++offset <= 2)
	{
		line += ft_strspn(line, " ");
		if ((color = cb_read_channel(color, line)) == -1)
			return (-1);
		line += ft_strspn(line, "0123456789");
		if (offset == 2 && *line != '\0')
			return (-1);
		line += ft_strspn(line, " ");
		if (offset < 2 && *line != ',')
			return (-1);
		line = (*line == ',') ? line + 1 : line;
	}
	color = mlx_get_color_value(cb->mlx_ptr, color);
	return (cb_set_color(cb, color, *temp_line));
}
