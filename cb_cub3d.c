/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 06:50:08 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/24 16:17:54 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>
//#include <stdlib.h>
#include <stdio.h>
#include "cb_cub3d.h"
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

void				cb_print_err(char *err_msg)//, int err)
{
	if (err_msg)// && err)
	{
//		write(2, "Error\n", 6);
		ft_putendl_fd("Error", 2);
		if (errno)
			perror(err_msg);
		else// if (*err_msg)
			ft_putendl_fd(err_msg, 2);
//		{
//			write(2, err_msg, ft_strlen(err_msg));
//			write(2, "\n", 1);
//		}
	}
}

int			cb_free_get_next_line_buf(int fd)
{
	get_next_line(fd, 0);
	return (-1);
}

void				cb_exit(t_cbdata *cbdata, char *err_msg)//, int err)
{
	cb_print_err(err_msg);//, err);
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
	}
	free(cbdata);
	if (err_msg)//(err)
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

static void			cb_print_floor_ceilling(t_cbdata *cbdata)
{
	int		height;
	int		width;
	int		*image;

	height = 0;
	width = 0;
	image = (int *)cbdata->frame->image;
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
		cb_exit(0, CB_ERR_NO_ARG);//, -1);
	if	(!(cbdata = cb_init()) ||
		!(cbdata->mlx_ptr = mlx_init()))
		cb_exit(cbdata, CB_ERR_INIT);//, -1);
	cb_parse_map_file(cbdata, argv[1]);

	cbdata->frame->img_ptr = mlx_new_image(cbdata->mlx_ptr, cbdata->frame->width, cbdata->frame->height);
	cbdata->frame->image = mlx_get_data_addr(cbdata->frame->img_ptr,
		&(cbdata->frame->bits_per_pixel), &(cbdata->frame->size_line), &(cbdata->frame->endian));

	if	(!(cbdata->win_ptr = mlx_new_window(cbdata->mlx_ptr, cbdata->frame->width,
											cbdata->frame->height, "cub3d")))
		cb_exit(cbdata, CB_ERR_WIN);//, -1);
//	print_bytes(cbdata->no_texture->image, cbdata->no_texture->size_line);
//	print_bytes(&(cbdata->floor_color), 4);
//	write(1, cbdata->no_texture->image, cbdata->no_texture->size_line);
//	write(1, "\n", 1);
	cb_print_floor_ceilling(cbdata);
	mlx_put_image_to_window(cbdata->mlx_ptr, cbdata->win_ptr,
							cbdata->frame->img_ptr, 0, 0);
	sleep(2);
	
	//free(ptr);
/*
	cb_draw_frame(cbdata);
	if (argc > 2 && !ft_strcmp(argv[2], "--save"))
		cb_save_image(cbdata->frame_ptr);
	mlx_put_image_to_window(mlx_ptr, win_ptr, cbdata->frame_ptr, 0, 0);
	mlx_destroy_image(cbdata->mlx_ptr, cbdata->frame_ptr);
	mlx_key_hook(win_ptr, cb_key_hook, cbdata);
*/

//	mlx_mouse_hook(win_ptr, cb_mouse_hook, map);
//	mlx_loop_hook(mlx_ptr, cb_loop_hook, map);
//	mlx_expose_hook(win_ptr, cb_expose, map);
//	mlx_loop(mlx_ptr);
	cb_exit(cbdata, 0);//, 0);
}
