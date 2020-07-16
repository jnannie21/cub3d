/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 06:50:08 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/14 09:37:53 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<unistd.h>
#include	"minilibx/mlx.h"

void	*mlx_init();

int		main(void)//int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 200, "my window");
	mlx_clear_window(mlx_ptr, win_ptr);
	sleep(10);
	mlx_destroy_window (mlx_ptr, win_ptr);
	return (0);
}

void	*cb_cub3d(void)
{
	return (0);
}