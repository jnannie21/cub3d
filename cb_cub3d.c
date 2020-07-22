/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 06:50:08 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/22 19:44:04 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>
//#include <stdlib.h>
#include "cb_cub3d.h"

void			cb_free_map(char **map)
{
	char	**temp_map;

	temp_map = map;
	if (map)
		while (*temp_map)
		{
			free(*temp_map);
			temp_map++;
		}
	free(map);
}

static int			cb_exit(t_cbdata *cbdata, int err)
{
	if (err == -1)
		write(1, "error\nsomething went wrong\n", 28);
	if (cbdata)
	{
		cb_free_map(cbdata->map);
		if (cbdata->mlx_ptr)
		{
			if (cbdata->no_texture->img_ptr)
				mlx_destroy_image(cbdata->mlx_ptr, cbdata->no_texture->img_ptr);
			if (cbdata->so_texture->img_ptr)
				mlx_destroy_image(cbdata->mlx_ptr, cbdata->so_texture->img_ptr);
			if (cbdata->we_texture->img_ptr)
				mlx_destroy_image(cbdata->mlx_ptr, cbdata->we_texture->img_ptr);
			if (cbdata->ea_texture->img_ptr)
				mlx_destroy_image(cbdata->mlx_ptr, cbdata->ea_texture->img_ptr);
			if (cbdata->sprite->img_ptr)
				mlx_destroy_image(cbdata->mlx_ptr, cbdata->sprite->img_ptr);
//			mlx_destroy_image(cbdata->mlx_ptr, cbdata->frame_ptr);
			if (cbdata->win_ptr)
			{
				//mlx_clear_window(cbdata->mlx_ptr, cbdata->win_ptr);
				mlx_destroy_window(cbdata->mlx_ptr, cbdata->win_ptr);
			}
		}
		free(cbdata->no_texture);
		free(cbdata->so_texture);
		free(cbdata->we_texture);
		free(cbdata->ea_texture);
		free(cbdata->sprite);
	}
	free(cbdata);
//	exit(EXIT_FAILURE);
	return (err);
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
	return (cbdata);
}

int					main(int argc, char **argv)
{
	t_cbdata	*cbdata;

	if (argc < 2 ||
		!(cbdata = cb_init()) ||
		!(cbdata->mlx_ptr = mlx_init()) ||
		cb_parse_map_file(cbdata, argv[1]) == -1 ||
		!(cbdata->win_ptr = mlx_new_window(cbdata->mlx_ptr, cbdata->win_width,
											cbdata->win_height, "cub3d")))
		return (cb_exit(cbdata, -1));
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
	return (cb_exit(cbdata, 0));
}
