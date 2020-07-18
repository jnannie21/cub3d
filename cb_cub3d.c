/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 06:50:08 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/18 08:55:22 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>
//#include <stdlib.h>
#include "minilibx/mlx.h"
#include "cb_cub3d.h"

int			main(int argc, char **argv)
{
	t_cbdata	*cbdata;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;

	if (!argv[1])
		return (0);
	cbdata = ft_calloc(sizeof(t_cbdata));
	cb_parse_map(cbdata, argv[1]);
	cbdata->mlx_ptr = mlx_init();
	cbdata->win_ptr = mlx_new_window(mlx_ptr, cbdata->win_width, cbdata->win_height, "cub3d");
	img_ptr = cb_draw_frame(cbdata);
	if (argv[2] && !ft_strcmp(argv[2], "--save"))
		cb_save_image(img_ptr);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_key_hook(win_ptr, cb_key_hook, cbdata);
//	mlx_mouse_hook(win_ptr, cb_mouse_hook, map);
//	mlx_loop_hook(mlx_ptr, cb_loop_hook, map);
//	mlx_expose_hook(win_ptr, cb_expose, map);
	mlx_loop(mlx_ptr);
//  mlx_clear_window(mlx_ptr, win_ptr);
//  mlx_destroy_window(mlx_ptr, win_ptr);
	return (0);
}
