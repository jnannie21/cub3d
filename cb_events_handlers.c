/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_events_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 03:30:56 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/29 01:54:34 by jnannie          ###   ########.fr       */
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

void	cb_move(t_cbdata *cbdata, double dir_x, double dir_y, int dir)
{
	int		dx;
	int		dy;

	dx = dir_x < 0 ? -1 : 1;
	dy = dir_y < 0 ? -1 : 1;
	if (cbdata->map[(int)(cbdata->pos_y)][(int)(cbdata->pos_x +/* dir_x * cbdata->moveSpeed * dir +*/ cbdata->moveSpeed * dir * dx *CB_INDENTATION)] == '0')// * CB_INDENTATION)] == '0')
		cbdata->pos_x += dir_x * cbdata->moveSpeed * dir;
	if (cbdata->map[(int)(cbdata->pos_y + /*dir_y * cbdata->moveSpeed * dir +*/ cbdata->moveSpeed * dir * dy * CB_INDENTATION)][(int)(cbdata->pos_x)] == '0')// * CB_INDENTATION)] == '0')
		cbdata->pos_y += dir_y * cbdata->moveSpeed * dir;
}

int		cb_loop_hook(void *cbdata)
{
	t_cbdata	*data;

	data = ((t_cbdata *)cbdata);
	mlx_do_sync(data->mlx_ptr);
	if (data->key_rot_left)
		cb_rotate_vectors(data, -data->rotate_speed);
	if (data->key_rot_right)
		cb_rotate_vectors(data, data->rotate_speed);
	if (data->key_left)
		cb_move(data, data->dir_x_perp, data->dir_y_perp, -1);
	if (data->key_right)
		cb_move(data, data->dir_x_perp, data->dir_y_perp, 1);
	if (data->key_up)
		cb_move(data, data->dir_x, data->dir_y, 1);
	if (data->key_down)
		cb_move(data, data->dir_x, data->dir_y, -1);
	cb_draw_frame(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
							data->frame->img_ptr, 0, 0);
	return (0);
}

int		cb_key_press_hook(int keycode, void *cbdata)
{
	if (keycode == CB_ESC)
		cb_exit(cbdata, 0);
	if (keycode == CB_LEFT)
		((t_cbdata *)cbdata)->key_rot_left = 1;
	else if (keycode == CB_RIGHT)
		((t_cbdata *)cbdata)->key_rot_right = 1;
	else if (keycode == CB_CAPITAL_A || keycode == CB_SMALL_A)
		((t_cbdata *)cbdata)->key_left = 1;
	else if (keycode == CB_CAPITAL_D || keycode == CB_SMALL_D)
		((t_cbdata *)cbdata)->key_right = 1;
	else if (keycode == CB_UP || keycode == CB_CAPITAL_W || keycode == CB_SMALL_W)
		((t_cbdata *)cbdata)->key_up = 1;
	else if (keycode == CB_DOWN || keycode == CB_CAPITAL_S || keycode == CB_SMALL_S)
		((t_cbdata *)cbdata)->key_down = 1;
	mlx_loop_hook(((t_cbdata *)cbdata)->mlx_ptr, cb_loop_hook, cbdata);
	return (0);
}

int		cb_key_release_hook(int keycode, void *cbdata)
{
	if (keycode == CB_LEFT)
		((t_cbdata *)cbdata)->key_rot_left = 0;
	else if (keycode == CB_RIGHT)
		((t_cbdata *)cbdata)->key_rot_right = 0;
	else if (keycode == CB_CAPITAL_A || keycode == CB_SMALL_A)
		((t_cbdata *)cbdata)->key_left = 0;
	else if (keycode == CB_CAPITAL_D || keycode == CB_SMALL_D)
		((t_cbdata *)cbdata)->key_right = 0;
	else if (keycode == CB_UP || keycode == CB_CAPITAL_W || keycode == CB_SMALL_W)
		((t_cbdata *)cbdata)->key_up = 0;
	else if (keycode == CB_DOWN || keycode == CB_CAPITAL_S || keycode == CB_SMALL_S)
		((t_cbdata *)cbdata)->key_down = 0;
	if (!((t_cbdata *)cbdata)->key_rot_left && !((t_cbdata *)cbdata)->key_rot_right &&
		!((t_cbdata *)cbdata)->key_left && !((t_cbdata *)cbdata)->key_right &&
		!((t_cbdata *)cbdata)->key_up && !((t_cbdata *)cbdata)->key_down)
		mlx_loop_hook(((t_cbdata *)cbdata)->mlx_ptr, 0, cbdata);
	return (0);
}