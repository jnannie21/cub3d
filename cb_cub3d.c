/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 06:50:08 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/18 03:12:11 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  <unistd.h>
#include  "minilibx/mlx.h"

//void  *mlx_init();

int    main(void)//int argc, char **argv)
{
  t_cbmap    *map;
  void    *mlx_ptr;
  void    *win_ptr;

  if (argv[1])
    map = cb_parse_map(argv[1]);
  mlx_ptr = mlx_init();
  win_ptr = mlx_new_window(mlx_ptr, map->width, map->height, "cub3d");
  mlx_key_hook (win_ptr, cb_key_hook, map);
  mlx_mouse_hook (win_ptr, cb_mouse_hook, map);
  mlx_loop_hook (mlx_ptr, cb_loop_hook, map);
  mlx_expose_hook (win_ptr, cb_expose, map);
  mlx_loop (mlx_ptr);
  mlx_clear_window(mlx_ptr, win_ptr);
  sleep(10);
  mlx_destroy_window (mlx_ptr, win_ptr);
  return (0);
}

void	*cb_cub3d(void)
{
	return (0);
}