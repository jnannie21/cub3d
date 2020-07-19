/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 14:45:02 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/19 19:49:20 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

static int	cb_read_resolution(t_cbdata *cbdata, char *line)
{
	line++;
	if ((cbdata->win_width = ft_atoi(line)) < 0)
		return (-1);
	line += ft_strspn(line, " ");
	line += ft_strspn(line, "0123456789");
	if ((cbdata->win_height = ft_atoi(line)) < 0)
		return (-1);
	return (0);
}

static int	cb_read_texture(t_cbdata *cbdata, char *line)
{
	void	*img_ptr;
	t_cbimage	*imgdata;

	line += 2;
	line += ft_strspn(line, " ");
	if (!ft_memcmp(line, "NO", 2))
		imgdata = cbdata->no_texture;
	else if (!ft_memcmp(line, "SO", 2))
		imgdata = cbdata->so_texture;
	else if (!ft_memcmp(line, "WE", 2))
		imgdata = cbdata->we_texture;
	else if (!ft_memcmp(line, "EA", 2))
		imgdata = cbdata->ea_texture;
	else if (!ft_memcmp(line, "S", 2))
		imgdata = cbdata->sprite;
	else
		return (-1);
	img_ptr = mlx_xpm_file_to_image(cbdata->mlx_ptr, line, &(imgdata->width),
														&(imgdata->height));
	imgdata->image = mlx_get_data_addr(img_ptr, &(imgdata->bits_per_pixel),
									&(imgdata->size_line), &(imgdata->endian));
	return (0);
}

static int	cb_read_color(&(cbdata->floor_color), line)
{

}

static int	cb_read_map_line(cbdata, line)
{

}

static int	cb_parse_line(t_cbdata *cbdata, char *line)
{
	if (*line == 'R')
		return (cb_read_resolution(&(cbdata->resolution), line));
	else if (ft_strchr("NSWE", *line))
		return (cb_read_texture(cbdata, line));
	else if (*line == 'F')
		return (cb_read_color(&(cbdata->floor_color), line));
	else if (*line == 'C')
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
