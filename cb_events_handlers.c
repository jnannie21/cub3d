/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_events_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 03:30:56 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/21 17:50:58 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"
//#include "minilibx/mlx.h"

#define ESC 0xff1b
#define LEFT 0xff51
#define RIGHT 0xff53
#define SMALL_W 0x0077
#define CAPITAL_W 0x0057
#define SMALL_S 0x0073
#define CAPITAL_S 0x0053
#define SMALL_A 0x0061
#define CAPITAL_A 0x0041
#define SMALL_D 0x0064
#define CAPITAL_D 0x0044

int		cb_key_hook(int keycode, void *cbdata)
{
	if (keycode == ESC)
		cb_exit(cbdata);
	else if (keycode == LEFT)
		cb_turn_left(cbdata);
	else if (keycode == RIGHT)
		cb_turn_right(cbdata);
	else if (keycode == SMALL_W || keycode == CAPITAL_W)
		cb_move_up(cbdata);
	else if (keycode == SMALL_S || keycode == CAPITAL_S)
		cb_move_down(cbdata);
	else if (keycode == SMALL_A || keycode == CAPITAL_A)
		cb_move_left(cbdata);
	else if (keycode == SMALL_D || keycode == CAPITAL_D)
		cb_move_right(cbdata);
	else
		return (0);
	cb_draw_frame(cbdata);
	mlx_put_image_to_window(((t_cbdata *)cbdata)->mlx_ptr,
							((t_cbdata *)cbdata)->win_ptr,
							((t_cbdata *)cbdata)->frame_ptr,
							0, 0);
	//mlx_destroy_image(((t_cbdata *)cbdata)->mlx_ptr,
	//					((t_cbdata *)cbdata)->img_ptr);
	return (0);
}