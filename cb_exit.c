/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 01:13:59 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/06 09:11:46 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"
#include <stdio.h>

static void			cb_print_err(char *err_msg)
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

static int			cb_free_get_next_line_buf(int fd)
{
	get_next_line(fd, 0);
	return (-1);
}

static void			cb_destroy_images(t_cbdata *cb)
{
	if (cb->frame && cb->frame->img_ptr)
		mlx_destroy_image(cb->mlx_ptr, cb->frame->img_ptr);
	if (cb->no_texture && cb->no_texture->img_ptr)
		mlx_destroy_image(cb->mlx_ptr, cb->no_texture->img_ptr);
	if (cb->so_texture && cb->so_texture->img_ptr)
		mlx_destroy_image(cb->mlx_ptr, cb->so_texture->img_ptr);
	if (cb->we_texture && cb->we_texture->img_ptr)
		mlx_destroy_image(cb->mlx_ptr, cb->we_texture->img_ptr);
	if (cb->ea_texture && cb->ea_texture->img_ptr)
		mlx_destroy_image(cb->mlx_ptr, cb->ea_texture->img_ptr);
	if (cb->sprite && cb->sprite->img_ptr)
		mlx_destroy_image(cb->mlx_ptr, cb->sprite->img_ptr);
	free(cb->frame);
	free(cb->no_texture);
	free(cb->so_texture);
	free(cb->we_texture);
	free(cb->ea_texture);
	free(cb->sprite);
}

void				cb_exit(t_cbdata *cb, char *err_msg)
{
	cb_print_err(err_msg);
	if (cb)
	{
		cb_free_map(cb->map);
		if (cb->mlx_ptr)
		{
			cb_destroy_images(cb);
			if (cb->win_ptr)
				mlx_destroy_window(cb->mlx_ptr, cb->win_ptr);
			free(cb->mlx_ptr);
		}
		cb_free_get_next_line_buf(cb->map_fd);
		free(cb->line);
		if (cb->map_fd != -1)
			close(cb->map_fd);
		free(cb->sprites);
		if (cb->rc)
			free(cb->rc->perp_dists);
		free(cb->rc);
		free(cb->sc);
	}
	free(cb);
	if (err_msg)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
