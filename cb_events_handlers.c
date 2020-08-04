/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_events_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 03:30:56 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/04 07:55:23 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"

#define CB_ESC 0xff1b
#define CB_LEFT 0xff51
#define CB_RIGHT 0xff53
#define CB_UP 0xff52
#define CB_DOWN 0xff54
#define CB_SMALL_W 0x0077
#define CB_CAPITAL_W 0x0057
#define CB_SMALL_S 0x0073
#define CB_CAPITAL_S 0x0053
#define CB_SMALL_A 0x0061
#define CB_CAPITAL_A 0x0041
#define CB_SMALL_D 0x0064
#define CB_CAPITAL_D 0x0044
#define CB_INDENTATION 2

void	cb_move(t_cbdata *cb, double dir_x, double dir_y, int dir)
{
	int		dx;
	int		dy;

	dx = dir_x < 0 ? -1 : 1;
	dy = dir_y < 0 ? -1 : 1;
	if (cb->map[(int)(cb->pos_y)][(int)(cb->pos_x +/* dir_x * cbdata->moveSpeed * dir +*/ cb->moveSpeed * dir * dx *CB_INDENTATION)] != '1')// * CB_INDENTATION)] == '0')
		cb->pos_x += dir_x * cb->moveSpeed * dir;
	if (cb->map[(int)(cb->pos_y + /*dir_y * cbdata->moveSpeed * dir +*/ cb->moveSpeed * dir * dy * CB_INDENTATION)][(int)(cb->pos_x)] != '1')// * CB_INDENTATION)] == '0')
		cb->pos_y += dir_y * cb->moveSpeed * dir;
}

int		cb_loop_hook(t_cbdata *cb)
{
	mlx_do_sync(cb->mlx_ptr);
	if (cb->key_rot_left)
		cb_rotate_vectors(cb, -cb->rotate_speed);
	if (cb->key_rot_right)
		cb_rotate_vectors(cb, cb->rotate_speed);
	if (cb->key_left)
		cb_move(cb, cb->dir_x_perp, cb->dir_y_perp, -1);
	if (cb->key_right)
		cb_move(cb, cb->dir_x_perp, cb->dir_y_perp, 1);
	if (cb->key_up || cb->key_w)
		cb_move(cb, cb->dir_x, cb->dir_y, 1);
	if (cb->key_down || cb->key_s)
		cb_move(cb, cb->dir_x, cb->dir_y, -1);
	cb_draw_frame(cb);
	mlx_put_image_to_window(cb->mlx_ptr, cb->win_ptr,
							cb->frame->img_ptr, 0, 0);
	return (0);
}

int		cb_key_press_hook(int keycode, t_cbdata *cb)
{
	if (keycode == CB_ESC)
		cb_exit(cb, 0);
	if (keycode == CB_LEFT)
		cb->key_rot_left = 1;
	else if (keycode == CB_RIGHT)
		cb->key_rot_right = 1;
	else if (keycode == CB_CAPITAL_A || keycode == CB_SMALL_A)
		cb->key_left = 1;
	else if (keycode == CB_CAPITAL_D || keycode == CB_SMALL_D)
		cb->key_right = 1;
	else if (keycode == CB_CAPITAL_W || keycode == CB_SMALL_W)
		cb->key_w = 1;
	else if (keycode == CB_UP)
		cb->key_up = 1;
	else if (keycode == CB_CAPITAL_S || keycode == CB_SMALL_S)
		cb->key_s = 1;
	else if (keycode == CB_DOWN)
		cb->key_down = 1;
	mlx_loop_hook(cb->mlx_ptr, cb_loop_hook, cb);
	return (0);
}

int		cb_key_release_hook(int keycode, t_cbdata *cb)
{
	if (keycode == CB_LEFT)
		cb->key_rot_left = 0;
	else if (keycode == CB_RIGHT)
		cb->key_rot_right = 0;
	else if (keycode == CB_CAPITAL_A || keycode == CB_SMALL_A)
		cb->key_left = 0;
	else if (keycode == CB_CAPITAL_D || keycode == CB_SMALL_D)
		cb->key_right = 0;
	else if (keycode == CB_CAPITAL_W || keycode == CB_SMALL_W)
		cb->key_w = 0;
	else if (keycode == CB_UP)
		cb->key_up = 0;
	else if (keycode == CB_CAPITAL_S || keycode == CB_SMALL_S)
		cb->key_s = 0;
	else if (keycode == CB_DOWN)
		cb->key_down = 0;
	if (!cb->key_rot_left && !cb->key_rot_right &&
		!cb->key_left && !cb->key_right &&
		!cb->key_up && !cb->key_down &&
		!cb->key_w && !cb->key_s)
		mlx_loop_hook(cb->mlx_ptr, 0, cb);
	return (0);
}

int		cb_expose_hook(t_cbdata *cb)
{
	cb_draw_frame(cb);
	mlx_put_image_to_window(cb->mlx_ptr, cb->win_ptr,
							cb->frame->img_ptr, 0, 0);
	return (0);
}

int		cb_destroy_hook(t_cbdata *cb)
{
	cb_exit(cb, 0);
	return (0);
}
