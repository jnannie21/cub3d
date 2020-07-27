/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_events_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 03:30:56 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/27 13:36:09 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d.h"
//#include "minilibx/mlx.h"
#include <math.h>

#define ESC 0xff1b
#define LEFT 0xff51
#define RIGHT 0xff53
#define UP 0xff52
#define DOWN 0xff54
#define SMALL_W 0x0077
#define CAPITAL_W 0x0057
#define SMALL_S 0x0073
#define CAPITAL_S 0x0053
#define SMALL_A 0x0061
#define CAPITAL_A 0x0041
#define SMALL_D 0x0064
#define CAPITAL_D 0x0044


int		cb_loop_hook(void *cbdata)
{
	double	moveSpeed;

	moveSpeed = 0.01;

	mlx_do_sync(((t_cbdata *)cbdata)->mlx_ptr);
	if (((t_cbdata *)cbdata)->left)
	{
		cb_rotate_vectors(cbdata, -M_PI / 150);
//		mlx_clear_window(((t_cbdata *)cbdata)->mlx_ptr, ((t_cbdata *)cbdata)->win_ptr);
		cb_print_floor_and_ceilling(cbdata);
		cb_draw_frame(cbdata);
		mlx_put_image_to_window(((t_cbdata *)cbdata)->mlx_ptr,
							((t_cbdata *)cbdata)->win_ptr,
							((t_cbdata *)cbdata)->frame->img_ptr,
							0, 0);
	}
	mlx_do_sync(((t_cbdata *)cbdata)->mlx_ptr);
//		cb_turn_left(cbdata);
	if (((t_cbdata *)cbdata)->right)
	{
		cb_rotate_vectors(cbdata, M_PI / 150);
//		mlx_clear_window(((t_cbdata *)cbdata)->mlx_ptr, ((t_cbdata *)cbdata)->win_ptr);
		cb_print_floor_and_ceilling(cbdata);
		cb_draw_frame(cbdata);
		mlx_put_image_to_window(((t_cbdata *)cbdata)->mlx_ptr,
							((t_cbdata *)cbdata)->win_ptr,
							((t_cbdata *)cbdata)->frame->img_ptr,
							0, 0);
	}
	mlx_do_sync(((t_cbdata *)cbdata)->mlx_ptr);
	if (((t_cbdata *)cbdata)->up)
	{
//		mlx_clear_window(((t_cbdata *)cbdata)->mlx_ptr, ((t_cbdata *)cbdata)->win_ptr);
		cb_print_floor_and_ceilling(cbdata);
		mlx_put_image_to_window(((t_cbdata *)cbdata)->mlx_ptr, ((t_cbdata *)cbdata)->win_ptr,
								((t_cbdata *)cbdata)->frame->img_ptr, 0, 0);
		if(((t_cbdata *)cbdata)->map[(int)(((t_cbdata *)cbdata)->pos_y)][(int)(((t_cbdata *)cbdata)->pos_x + ((t_cbdata *)cbdata)->dir_x * moveSpeed)] == '0')
			((t_cbdata *)cbdata)->pos_x += ((t_cbdata *)cbdata)->dir_x * moveSpeed;
		if(((t_cbdata *)cbdata)->map[(int)(((t_cbdata *)cbdata)->pos_y + ((t_cbdata *)cbdata)->dir_y * moveSpeed)][(int)((t_cbdata *)cbdata)->pos_x] == '0')
			((t_cbdata *)cbdata)->pos_y += ((t_cbdata *)cbdata)->dir_y * moveSpeed;
		cb_draw_frame(cbdata);
		mlx_put_image_to_window(((t_cbdata *)cbdata)->mlx_ptr,
							((t_cbdata *)cbdata)->win_ptr,
							((t_cbdata *)cbdata)->frame->img_ptr,
							0, 0);
	}
	mlx_do_sync(((t_cbdata *)cbdata)->mlx_ptr);
	if (((t_cbdata *)cbdata)->down)
	{
//		mlx_clear_window(((t_cbdata *)cbdata)->mlx_ptr, ((t_cbdata *)cbdata)->win_ptr);
		cb_print_floor_and_ceilling(cbdata);
		mlx_put_image_to_window(((t_cbdata *)cbdata)->mlx_ptr, ((t_cbdata *)cbdata)->win_ptr,
								((t_cbdata *)cbdata)->frame->img_ptr, 0, 0);
		if(((t_cbdata *)cbdata)->map[(int)(((t_cbdata *)cbdata)->pos_y)][(int)(((t_cbdata *)cbdata)->pos_x - ((t_cbdata *)cbdata)->dir_x * moveSpeed)] == '0')
			((t_cbdata *)cbdata)->pos_x -= ((t_cbdata *)cbdata)->dir_x * moveSpeed;
		if(((t_cbdata *)cbdata)->map[(int)(((t_cbdata *)cbdata)->pos_y - ((t_cbdata *)cbdata)->dir_y * moveSpeed)][(int)((t_cbdata *)cbdata)->pos_x] == '0')
			((t_cbdata *)cbdata)->pos_y -= ((t_cbdata *)cbdata)->dir_y * moveSpeed;
		cb_draw_frame(cbdata);
		mlx_put_image_to_window(((t_cbdata *)cbdata)->mlx_ptr,
							((t_cbdata *)cbdata)->win_ptr,
							((t_cbdata *)cbdata)->frame->img_ptr,
							0, 0);
	}
//	mlx_key_hook(((t_cbdata *)cbdata)->win_ptr, cb_key_hook, ((t_cbdata *)cbdata));

/*		cb_turn_right(cbdata);
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

	if (keycode == RIGHT)
		mlx_put_image_to_window(((t_cbdata *)cbdata)->mlx_ptr,
							((t_cbdata *)cbdata)->win_ptr,
							((t_cbdata *)cbdata)->frame->img_ptr,
							0, 0);
	*/
	//mlx_destroy_image(((t_cbdata *)cbdata)->mlx_ptr,
	//					((t_cbdata *)cbdata)->img_ptr);
	return (0);

/*
	cb_print_floor_and_ceilling(cbdata);
	mlx_put_image_to_window(((t_cbdata *)cbdata)->mlx_ptr, ((t_cbdata *)cbdata)->win_ptr,
							((t_cbdata *)cbdata)->frame->img_ptr, 0, 0);
	cb_draw_frame(cbdata);
	mlx_put_image_to_window(((t_cbdata *)cbdata)->mlx_ptr, ((t_cbdata *)cbdata)->win_ptr,
							((t_cbdata *)cbdata)->frame->img_ptr, 0, 0);
	return (0);
*/
}

int		cb_key_press_hook(int keycode, void *cbdata)
{
	if (keycode == ESC)
		cb_exit(cbdata, 0);//, 0);
	if (keycode == LEFT)
	{
		((t_cbdata *)cbdata)->left = 1;
	}
	if (keycode == RIGHT)
	{
		((t_cbdata *)cbdata)->right = 1;
	}

	if (keycode == UP)
	{
		((t_cbdata *)cbdata)->up = 1;
	}

	if (keycode == DOWN)
	{
		((t_cbdata *)cbdata)->down = 1;
	}
	mlx_loop_hook(((t_cbdata *)cbdata)->mlx_ptr, cb_loop_hook, cbdata);
	return (0);
}

int		cb_key_release_hook(int keycode, void *cbdata)
{
	if (keycode == LEFT)
	{
		((t_cbdata *)cbdata)->left = 0;
	}
	else if (keycode == RIGHT)
	{
		((t_cbdata *)cbdata)->right = 0;
	}

	else if (keycode == UP)
	{
		((t_cbdata *)cbdata)->up = 0;
	}

	else if (keycode == DOWN)
	{
		((t_cbdata *)cbdata)->down = 0;
	}
	if (!((t_cbdata *)cbdata)->left && !((t_cbdata *)cbdata)->right &&
		!((t_cbdata *)cbdata)->up && !((t_cbdata *)cbdata)->down)
		mlx_loop_hook(((t_cbdata *)cbdata)->mlx_ptr, 0, cbdata);
	return (0);
}