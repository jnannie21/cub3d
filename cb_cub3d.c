/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 06:50:08 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/31 15:20:42 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cb_cub3d.h"
#include <math.h>

#define CB_KEYPRESS 2
#define CB_KEYRELEASE 3
#define CB_KEYPRESSMASK (1L<<0)
#define CB_KEYRELEASEMASK (1L<<1)

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
	if	(!(cbdata->win_ptr = mlx_new_window(cbdata->mlx_ptr, cbdata->frame->width,
											cbdata->frame->height, "cub3d")))
		cb_exit(cbdata, CB_ERR_WIN);
	cb_draw_frame(cbdata);
	mlx_put_image_to_window(cbdata->mlx_ptr, cbdata->win_ptr,
							cbdata->frame->img_ptr, 0, 0);
	mlx_do_key_autorepeaton(cbdata->mlx_ptr);
	mlx_hook(cbdata->win_ptr, CB_KEYPRESS, CB_KEYPRESSMASK,
		 cb_key_press_hook, cbdata);
	mlx_hook(cbdata->win_ptr, CB_KEYRELEASE, CB_KEYRELEASEMASK,
		 cb_key_release_hook, cbdata);

//	mlx_mouse_hook(win_ptr, cb_mouse_hook, map);
//	mlx_loop_hook(cbdata->mlx_ptr, cb_loop_hook, cbdata);
//	mlx_expose_hook(win_ptr, cb_expose, map);
	mlx_loop(cbdata->mlx_ptr);
}
