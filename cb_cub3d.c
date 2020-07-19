/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 06:50:08 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/19 17:20:19 by jnannie          ###   ########.fr       */
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

	if (argc < 1 ||
		!(cb_init(cbdata)) ||
		cb_parse_map(cbdata, argv[1]) == -1)
		return (cb_error(cbdata));
	cbdata->mlx_ptr = mlx_init();
	cbdata->win_ptr = mlx_new_window(mlx_ptr, cbdata->win_width,
									cbdata->win_height, "cub3d");
	cb_draw_frame(cbdata);
	if (argv[2] && !ft_strcmp(argv[2], "--save"))
		cb_save_image(cbdata->frame_ptr);
	mlx_put_image_to_window(mlx_ptr, win_ptr, cbdata->frame_ptr, 0, 0);
	mlx_destroy_image(cbdata->mlx_ptr, cbdata->frame_ptr);
	mlx_key_hook(win_ptr, cb_key_hook, cbdata);
//	mlx_mouse_hook(win_ptr, cb_mouse_hook, map);
//	mlx_loop_hook(mlx_ptr, cb_loop_hook, map);
//	mlx_expose_hook(win_ptr, cb_expose, map);
	mlx_loop(mlx_ptr);
//  mlx_clear_window(mlx_ptr, win_ptr);
//  mlx_destroy_window(mlx_ptr, win_ptr);
	return (0);
}
