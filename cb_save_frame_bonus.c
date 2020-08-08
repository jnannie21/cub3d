/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_save_frame_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 06:05:03 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/08 12:22:02 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d_bonus.h"

static int				cb_write_headers(t_cbdata *cb, int fd,
											int image_size)
{
	t_bmp_file_header	file_header;
	t_bmp_image_header	image_header;

	ft_memset(&file_header, '\0', 14);
	ft_memset(&image_header, '\0', sizeof(t_bmp_image_header));
	ft_memcpy(file_header.bitmap_type, "BM", 2);
	file_header.file_size = 54 + image_size;
	file_header.reserved1 = 0;
	file_header.reserved2 = 0;
	file_header.offset_bits = 0;
	image_header.size_header = sizeof(t_bmp_image_header);
	image_header.width = cb->frame->width;
	image_header.height = -cb->frame->height;
	image_header.color_planes = 1;
	image_header.bitsperpixel = 32;
	image_header.compression = 0;
	image_header.image_size = image_size;
	image_header.ppm_x = 2835;
	image_header.ppm_y = 2835;
	image_header.numcolorspallette = 0;
	image_header.numcolorsused = 0;
	if (write(fd, &file_header, 14) == -1 ||
		write(fd, &image_header, sizeof(t_bmp_image_header)) == -1)
		return (-1);
	return (0);
}

static int				cb_quit(int fd, int err)
{
	close(fd);
	return (err);
}

int						cb_save_frame(t_cbdata *cb)
{
	int					fd;
	int					image_size;

	image_size = cb->frame->width * cb->frame->height * 4;
	if ((fd = open(CB_IMAGE_FILENAME, O_WRONLY | O_CREAT | O_TRUNC)) == -1)
		return (-1);
	if (cb_write_headers(cb, fd, image_size) == -1
		|| write(fd, cb->frame->image, image_size) == -1)
		return (cb_quit(fd, -1));
	return (cb_quit(fd, 0));
}
