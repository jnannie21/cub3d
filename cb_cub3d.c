/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 06:50:08 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/03 01:46:06 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cb_cub3d.h"
#include <math.h>

#define CB_KEYPRESS 2
#define CB_KEYRELEASE 3
#define CB_DESTROYNOTIFY 17
#define CB_KEYPRESSMASK (1L<<0)
#define CB_KEYRELEASEMASK (1L<<1)
#define CB_SUBSTRUCTURENOTIFYMASK (1L<<17)

/*
void				print_bytes(void *ptr, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
		printf("%02hhX ", ((unsigned char *)ptr)[i++]);
	printf("\n");
}
*/
void			cb_free_map(char **map)
{
	char	**temp_map;

	temp_map = map;
	if (temp_map)
		while (*temp_map)
		{
			free(*temp_map);
			temp_map++;
		}
	free(map);
}

void				cb_print_err(char *err_msg)
{
	if (err_msg)
	{
		ft_putendl_fd("Error", 2);
		if (errno)
			perror(err_msg);
		else
			ft_putendl_fd(err_msg, 2);
	}
}

int			cb_free_get_next_line_buf(int fd)
{
	get_next_line(fd, 0);
	return (-1);
}

void				cb_exit(t_cbdata *cbdata, char *err_msg)
{
	cb_print_err(err_msg);
	if (cbdata)
	{
		cb_free_map(cbdata->map);
		if (cbdata->mlx_ptr)
		{
			if (cbdata->frame && cbdata->frame->img_ptr)
				mlx_destroy_image(cbdata->mlx_ptr, cbdata->frame->img_ptr);
			if (cbdata->no_texture && cbdata->no_texture->img_ptr)
				mlx_destroy_image(cbdata->mlx_ptr, cbdata->no_texture->img_ptr);
			if (cbdata->so_texture && cbdata->so_texture->img_ptr)
				mlx_destroy_image(cbdata->mlx_ptr, cbdata->so_texture->img_ptr);
			if (cbdata->we_texture && cbdata->we_texture->img_ptr)
				mlx_destroy_image(cbdata->mlx_ptr, cbdata->we_texture->img_ptr);
			if (cbdata->ea_texture && cbdata->ea_texture->img_ptr)
				mlx_destroy_image(cbdata->mlx_ptr, cbdata->ea_texture->img_ptr);
			if (cbdata->sprite && cbdata->sprite->img_ptr)
				mlx_destroy_image(cbdata->mlx_ptr, cbdata->sprite->img_ptr);
			if (cbdata->win_ptr)
				mlx_destroy_window(cbdata->mlx_ptr, cbdata->win_ptr);
		}
		free(cbdata->frame);
		free(cbdata->no_texture);
		free(cbdata->so_texture);
		free(cbdata->we_texture);
		free(cbdata->ea_texture);
		free(cbdata->sprite);
		cb_free_get_next_line_buf(cbdata->fd);
		free(cbdata->line);
		if (cbdata->fd != -1)
			close(cbdata->fd);
		free(cbdata->sprites);
	}
	free(cbdata);
	if (err_msg)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

static t_cbdata		*cb_init(void)
{
	t_cbdata	*cbdata;

	if (!(cbdata = ft_calloc(1, sizeof(t_cbdata))) ||
		!(cbdata->frame = ft_calloc(1, sizeof(t_cbimage))) ||
		!(cbdata->no_texture = ft_calloc(1, sizeof(t_cbimage))) ||
		!(cbdata->so_texture = ft_calloc(1, sizeof(t_cbimage))) ||
		!(cbdata->we_texture = ft_calloc(1, sizeof(t_cbimage))) ||
		!(cbdata->ea_texture = ft_calloc(1, sizeof(t_cbimage))) ||
		!(cbdata->sprite = ft_calloc(1, sizeof(t_cbimage))))
		return (0);
	cbdata->floor_color = 0x80000000;
	cbdata->ceilling_color = 0x80000000;
	cbdata->fd = -1;
	return (cbdata);
}
/*
unsigned int		cb_color_to_big_endian(unsigned int color)
{
	unsigned int		new_color;
	unsigned int		straight_mask;
	unsigned int		inverse_mask;

	new_color = 0;
	straight_mask = 1;
	inverse_mask = 1 << 31;
	while (straight_mask)
	{
		if (color & straight_mask)
			new_color |= inverse_mask;
		straight_mask <<= 1;
		inverse_mask >>= 1;
	}
	return (new_color);
}
*/
void			cb_print_floor_and_ceilling(t_cbdata *cbdata)
{
	int		height;
	int		width;
	int		*image;

	height = 0;
	width = 0;
	image = (int *)cbdata->frame->image;
//	if (cbdata->frame->endian)
//	{
//		cbdata->floor_color = cb_color_to_big_endian(cbdata->floor_color);
//		cbdata->ceilling_color = cb_color_to_big_endian(cbdata->ceilling_color);
//	}
	while (height < cbdata->frame->height)
	{
		while (width < cbdata->frame->width)
		{
			if (height < cbdata->frame->height / 2)
				*image = cbdata->ceilling_color;
			else
				*image = cbdata->floor_color;
			image++;
			width++;
		}
		width = 0;
		height++;
	}
}

static int			cb_put_image_to_file(t_cbdata *cbdata)
{
	int image_size = cbdata->frame->width * cbdata->frame->height * 3;
	int file_size = 54 + image_size;
	int ppm = 2835;

	struct bitmap_file_header {
		unsigned char   bitmap_type[2];     // 2 bytes
		int             file_size;          // 4 bytes
		short           reserved1;          // 2 bytes
		short           reserved2;          // 2 bytes
		unsigned int    offset_bits;        // 4 bytes
	} bfh;

	// bitmap image header (40 bytes)
	struct bitmap_image_header {
		unsigned int    size_header;        // 4 bytes
		unsigned int    width;              // 4 bytes
		unsigned int    height;             // 4 bytes
		short int       planes;             // 2 bytes
		short int       bit_count;          // 2 bytes
		unsigned int    compression;        // 4 bytes
		unsigned int    image_size;         // 4 bytes
		unsigned int    ppm_x;              // 4 bytes
		unsigned int    ppm_y;              // 4 bytes
		unsigned int    clr_used;           // 4 bytes
		unsigned int    clr_important;      // 4 bytes
	} bih;

	ft_memcpy(&bfh.bitmap_type, "BM", 2);
	bfh.file_size       = file_size;
	bfh.reserved1       = 0;
	bfh.reserved2       = 0;
	bfh.offset_bits     = 0;

	bih.size_header     = sizeof(bih);
	bih.width           = cbdata->frame->width;
	bih.height          = -cbdata->frame->height;
	bih.planes          = 1;
	bih.bit_count       = 24;
	bih.compression     = 0;
	bih.image_size      = cbdata->frame->width * cbdata->frame->height;
	bih.ppm_x           = ppm;
	bih.ppm_y           = ppm;
	bih.clr_used        = 0;
	bih.clr_important   = 0;

	int fd;

	if ((fd = open(CB_IMAGE_FILENAME, O_WRONLY  | O_CREAT | O_TRUNC)) == -1)
		return (-1);
	if (write(fd, &bfh, 14) == -1 ||
		write(fd, &bih, sizeof(bih)) == -1)
		return (-1);
	char *image = ft_calloc(1, image_size);
	int i = 0;
	int j = 0;

	while (i < (cbdata->frame->width * cbdata->frame->height * 4))
	{
		ft_memcpy(image + j, cbdata->frame->image + i, 3);
		i += 4;
		j += 3;
	}
	if (write(fd, image, image_size) == -1)
		return (-1);
	close(fd);
	return (0);
}

int					main(int argc, char **argv)
{
	t_cbdata	*cbdata;

	if (argc < 2)
		cb_exit(0, CB_ERR_NO_ARG);
	if	(!(cbdata = cb_init()) ||
		!(cbdata->mlx_ptr = mlx_init()))
		cb_exit(cbdata, CB_ERR_INIT);
	cb_parse_map_file(cbdata, argv[1]);
	cbdata->moveSpeed = ((double)(cbdata->frame->height * cbdata->frame->width) / (30000000.0));
	cbdata->rotate_speed = M_PI * ((double)(cbdata->frame->height * cbdata->frame->width) / (90000000.0));
	cbdata->frame->img_ptr = mlx_new_image(cbdata->mlx_ptr, cbdata->frame->width, cbdata->frame->height);
	cbdata->frame->image = mlx_get_data_addr(cbdata->frame->img_ptr,
		&(cbdata->frame->bits_per_pixel), &(cbdata->frame->size_line), &(cbdata->frame->endian));
	if (argc > 2 && ft_memcmp(argv[2], "--save", 7) == 0)
	{
		cb_draw_frame(cbdata);
		if (cb_put_image_to_file(cbdata) == -1)
			cb_exit(cbdata, CB_ERR_IMAGE_SAVE);
		cb_exit(cbdata, 0);
	}
	if	(!(cbdata->win_ptr = mlx_new_window(cbdata->mlx_ptr, cbdata->frame->width,
											cbdata->frame->height, "cub3d")))
		cb_exit(cbdata, CB_ERR_WIN);
	mlx_do_key_autorepeaton(cbdata->mlx_ptr);
	mlx_hook(cbdata->win_ptr, CB_KEYPRESS, CB_KEYPRESSMASK,
		 cb_key_press_hook, cbdata);
	mlx_hook(cbdata->win_ptr, CB_KEYRELEASE, CB_KEYRELEASEMASK,
		 cb_key_release_hook, cbdata);
	mlx_hook(cbdata->win_ptr, CB_DESTROYNOTIFY, CB_SUBSTRUCTURENOTIFYMASK,
		 cb_destroy_hook, cbdata);
	mlx_expose_hook(cbdata->win_ptr, cb_expose_hook, cbdata);
	mlx_loop(cbdata->mlx_ptr);
}
