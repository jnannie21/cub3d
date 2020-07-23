/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 06:50:08 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/23 23:29:04 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>
//#include <stdlib.h>
#include <stdio.h>
#include "cb_cub3d.h"

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

void				cb_print_err(char *err_msg, int err)
{
	if (err && err_msg)
	{
		write(2, "Error\n", 6);
		if (errno)
			perror(err_msg);
		else// if (*err_msg)
		{
			write(2, err_msg, ft_strlen(err_msg));
			write(2, "\n", 1);
		}
	}
}

void				cb_exit(t_cbdata *cbdata, char *err_msg, int err)
{
	cb_print_err(err_msg, err);
	if (cbdata)
	{
		cb_free_map(cbdata->map);
		if (cbdata->mlx_ptr)
		{
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
//			mlx_destroy_image(cbdata->mlx_ptr, cbdata->frame_ptr);
			if (cbdata->win_ptr)
				mlx_destroy_window(cbdata->mlx_ptr, cbdata->win_ptr);
		}
		free(cbdata->no_texture);
		free(cbdata->so_texture);
		free(cbdata->we_texture);
		free(cbdata->ea_texture);
		free(cbdata->sprite);
		cb_free_get_next_line_buf(cbdata->fd);
		free(cbdata->line);
	}
	free(cbdata);
	if (err)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

static t_cbdata		*cb_init(void)
{
	t_cbdata	*cbdata;

	if (!(cbdata = ft_calloc(1, sizeof(t_cbdata))) ||
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

int					main(int argc, char **argv)
{
	t_cbdata	*cbdata;

	if (argc < 2)
		cb_exit(0, CB_ERR_NO_ARG, -1);
	if	(!(cbdata = cb_init()) ||
		!(cbdata->mlx_ptr = mlx_init()))
		cb_exit(cbdata, CB_ERR_INIT, -1);
	cb_parse_map_file(cbdata, argv[1]);
	if	(!(cbdata->win_ptr = mlx_new_window(cbdata->mlx_ptr, cbdata->win_width,
											cbdata->win_height, "cub3d")))
		cb_exit(cbdata, CB_ERR_WIN, -1);
	mlx_put_image_to_window(cbdata->mlx_ptr, cbdata->win_ptr,
							cbdata->no_texture->img_ptr, 100, 0);
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
	cb_exit(cbdata, 0, 0);
}
