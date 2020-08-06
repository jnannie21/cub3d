/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_save_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 06:05:03 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/06 02:32:54 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"

static int				cb_write_headers(t_cbdata *cb, int fd,
											int bmp_image_size)
{
	t_bmp_file_header	file_header;
	t_bmp_image_header	image_header;

	ft_memcpy(file_header.bitmap_type, "BM", 2);
	file_header.file_size = 54 + bmp_image_size;
	file_header.reserved1 = 0;
	file_header.reserved2 = 0;
	file_header.offset_bits = 0;
	image_header.size_header = 40;
	image_header.width = cb->frame->width;
	image_header.height = -cb->frame->height;
	image_header.color_planes = 1;
	image_header.bitsperpixel = 24;
	image_header.compression = 0;
	image_header.image_size = bmp_image_size;
	image_header.ppm_x = 2835;
	image_header.ppm_y = 2835;
	image_header.numcolorspallette = 0;
	image_header.numcolorsused = 0;
	if (write(fd, &file_header, 14) == -1 ||
		write(fd, &image_header, sizeof(t_bmp_image_header)) == -1)
		return (-1);
	return (0);
}

static void				cb_get_pixel_data(char *bmp_image, char *frame_image,
											int frame_image_size)
{
	int					i;
	int					j;

	i = 0;
	j = 0;
	while (i < frame_image_size)
	{
		ft_memcpy(bmp_image + j, frame_image + i, 3);
		i += 4;
		j += 3;
	}
}

int						cb_save_frame(t_cbdata *cb)
{
	int					fd;
	int					bmp_image_size;
	char				*bmp_image;

	bmp_image_size = cb->frame->width * cb->frame->height * 3;
	if ((fd = open(CB_IMAGE_FILENAME, O_WRONLY | O_CREAT | O_TRUNC)) == -1)
		return (-1);
	if (!(bmp_image = ft_calloc(1, bmp_image_size))
		|| cb_write_headers(cb, fd, bmp_image_size) == -1)
	{
		close(fd);
		return (-1);
	}
	cb_get_pixel_data(bmp_image, cb->frame->image,
		cb->frame->width * cb->frame->height * 4);
	if (write(fd, bmp_image, bmp_image_size) == -1)
		return (-1);
	close(fd);
	return (0);
}
