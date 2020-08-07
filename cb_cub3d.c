/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 06:50:08 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/07 08:09:31 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"

#define CB_KEYPRESS 2
#define CB_KEYRELEASE 3
#define CB_DESTROYNOTIFY 17
#define CB_KEYPRESSMASK (1L<<0)
#define CB_KEYRELEASEMASK (1L<<1)
#define CB_SUBSTRUCTURENOTIFYMASK (1L<<17)

static int			cb_alloc_textures(t_cbdata *cb)
{
	if (!(cb->frame = ft_calloc(1, sizeof(t_cbimage)))
		|| !(cb->no_texture = ft_calloc(1, sizeof(t_cbimage)))
		|| !(cb->so_texture = ft_calloc(1, sizeof(t_cbimage)))
		|| !(cb->we_texture = ft_calloc(1, sizeof(t_cbimage)))
		|| !(cb->ea_texture = ft_calloc(1, sizeof(t_cbimage)))
		|| !(cb->sprite = ft_calloc(1, sizeof(t_cbimage)))
		|| !(cb->bonus_sprite = ft_calloc(1, sizeof(t_cbimage))))
		return (-1);
	return (0);
}

static t_cbdata		*cb_init(char *filename)
{
	t_cbdata	*cb;

	if (!(cb = ft_calloc(1, sizeof(t_cbdata)))
		|| !(cb->mlx_ptr = mlx_init())
		|| cb_alloc_textures(cb) == -1)
		cb_exit(cb, CB_ERR_INIT);
	cb->floor_color = 0x80000000;
	cb->ceilling_color = 0x80000000;
	cb->map_fd = -1;
	cb_parse_map_file(cb, filename);
	cb->move_speed = ((double)(cb->frame->height * cb->frame->width)
		/ (30000000.0));
	cb->rotate_speed = M_PI * ((double)(cb->frame->height * cb->frame->width)
		/ (150000000.0));
	if (!(cb->frame->img_ptr = mlx_new_image(cb->mlx_ptr, cb->frame->width,
											cb->frame->height)))
		cb_exit(cb, CB_ERR_INIT);
	cb->frame->image = mlx_get_data_addr(cb->frame->img_ptr,
		&(cb->frame->bits_per_pixel), &(cb->frame->size_line),
		&(cb->frame->endian));
	if (!(cb->rc = ft_calloc(1, sizeof(t_cbraycaster)))
		|| !(cb->rc->perp_dists = ft_calloc(cb->frame->width, sizeof(double)))
		|| !(cb->sc = ft_calloc(1, sizeof(t_cbscreen))))
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
	if (!(cb->win_ptr = mlx_new_window(cb->mlx_ptr, cb->frame->width,
								cb->frame->height, CB_WINDOW_TITLE)))
		cb_exit(cb, CB_ERR_WIN);
	mlx_do_key_autorepeaton(cb->mlx_ptr);
	cb_hooks(cb);
	mlx_loop(cb->mlx_ptr);
}
