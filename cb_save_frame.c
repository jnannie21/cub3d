/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_save_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 06:05:03 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/05 20:31:09 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"

static int				cb_write_headers(t_cbdata *cb, int fd, int image_size)
{
	t_bmp_file_header	file_header;
	t_bmp_image_header	image_header;

	ft_memcpy(file_header.bitmap_type, "BM", 2);
	file_header.file_size = 54 + image_size;
	file_header.reserved1 = 0;
	file_header.reserved2 = 0;
	file_header.offset_bits = 0;
	image_header.size_header = 40;
	image_header.width = cb->frame->width;
	image_header.height = -cb->frame->height;
	image_header.planes = 1;
	image_header.bit_count = 24;
	image_header.compression = 0;
	image_header.image_size = image_size;
	image_header.ppm_x = 2835;
	image_header.ppm_y = 2835;
	image_header.clr_used = 0;
	image_header.clr_important = 0;
	if (write(fd, &file_header, 14) == -1 ||
		write(fd, &image_header, sizeof(t_bmp_image_header)) == -1)
		return (-1);
	return (0);
}

int						cb_save_frame(t_cbdata *cb)
{
	int					fd;
	int					image_size;
	char				*image;
	int					i;
	int					j;

	image_size = cb->frame->width * cb->frame->height * 3;
	if ((fd = open(CB_IMAGE_FILENAME, O_WRONLY  | O_CREAT | O_TRUNC)) == -1
	|| cb_write_headers(cb, fd, image_size) == -1)
		return (-1);
	image = ft_calloc(1, image_size);
	i = 0;
	j = 0;
	while (i < (cb->frame->width * cb->frame->height * 4))
	{
		ft_memcpy(image + j, cb->frame->image + i, 3);
		i += 4;
		j += 3;
	}
	if (write(fd, image, image_size) == -1)
		return (-1);
	close(fd);
	return (0);
}

