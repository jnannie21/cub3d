/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 06:50:08 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/05 09:14:34 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cb_cub3d.h"

#define CB_KEYPRESS 2
#define CB_KEYRELEASE 3
#define CB_DESTROYNOTIFY 17
#define CB_KEYPRESSMASK (1L<<0)
#define CB_KEYRELEASEMASK (1L<<1)
#define CB_SUBSTRUCTURENOTIFYMASK (1L<<17)

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

void				cb_exit(t_cbdata *cb, char *err_msg)
{
	cb_print_err(err_msg);
	if (cb)
	{
		cb_free_map(cb->map);
		if (cb->mlx_ptr)
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
			if (cb->win_ptr)
				mlx_destroy_window(cb->mlx_ptr, cb->win_ptr);
		}
		free(cb->frame);
		free(cb->no_texture);
		free(cb->so_texture);
		free(cb->we_texture);
		free(cb->ea_texture);
		free(cb->sprite);
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

static t_cbdata		*cb_init(char *filename)
{
	t_cbdata	*cb;

	if (!(cb = ft_calloc(1, sizeof(t_cbdata))) ||
		!(cb->frame = ft_calloc(1, sizeof(t_cbimage))) ||
		!(cb->no_texture = ft_calloc(1, sizeof(t_cbimage))) ||
		!(cb->so_texture = ft_calloc(1, sizeof(t_cbimage))) ||
		!(cb->we_texture = ft_calloc(1, sizeof(t_cbimage))) ||
		!(cb->ea_texture = ft_calloc(1, sizeof(t_cbimage))) ||
		!(cb->sprite = ft_calloc(1, sizeof(t_cbimage))) ||
		!(cb->mlx_ptr = mlx_init()))
		cb_exit(cb, CB_ERR_INIT);
	cb->floor_color = 0x80000000;
	cb->ceilling_color = 0x80000000;
	cb->map_fd = -1;
	cb_parse_map_file(cb, filename);
	cb->moveSpeed = ((double)(cb->frame->height * cb->frame->width) / (30000000.0));
	cb->rotate_speed = M_PI * ((double)(cb->frame->height * cb->frame->width) / (90000000.0));
	if (!(cb->frame->img_ptr = mlx_new_image(cb->mlx_ptr, cb->frame->width, cb->frame->height)))
		cb_exit(cb, CB_ERR_INIT);
	cb->frame->image = mlx_get_data_addr(cb->frame->img_ptr,
		&(cb->frame->bits_per_pixel), &(cb->frame->size_line), &(cb->frame->endian));
	if (!(cb->rc = ft_calloc(1, sizeof(t_cbraycaster))) ||
		!(cb->rc->perp_dists = ft_calloc(cb->frame->width, sizeof(double))) ||
		!(cb->sc = ft_calloc(1, sizeof(t_cbscreen))))
		cb_exit(cb, CB_ERR_INIT);
	return (cb);
}

static void			cb_hooks(t_cbdata *cb)
{
	mlx_hook(cb->win_ptr, CB_KEYPRESS, CB_KEYPRESSMASK,
		 cb_key_press_hook, cb);
	mlx_hook(cb->win_ptr, CB_KEYRELEASE, CB_KEYRELEASEMASK,
		 cb_key_release_hook, cb);
	mlx_hook(cb->win_ptr, CB_DESTROYNOTIFY, CB_SUBSTRUCTURENOTIFYMASK,
		 cb_destroy_hook, cb);
	mlx_expose_hook(cb->win_ptr, cb_expose_hook, cb);
}

int					main(int argc, char **argv)
{
	t_cbdata	*cb;

	if (argc < 2)
		cb_exit(0, CB_ERR_NO_ARG);
	cb = cb_init(argv[1]);
	if (argc > 2 && ft_memcmp(argv[2], "--save", 7) == 0)
	{
		cb_draw_frame(cb);
		if (cb_save_frame(cb) == -1)
			cb_exit(cb, CB_ERR_IMAGE_SAVE);
		cb_exit(cb, 0);
	}
	if	(!(cb->win_ptr = mlx_new_window(cb->mlx_ptr, cb->frame->width,
											cb->frame->height, "cub3d")))
		cb_exit(cb, CB_ERR_WIN);
	mlx_do_key_autorepeaton(cb->mlx_ptr);
	cb_hooks(cb);
	mlx_loop(cb->mlx_ptr);
}
