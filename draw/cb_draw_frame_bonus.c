/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_draw_frame_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 21:49:44 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/07 11:55:18 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cb_cub3d_bonus.h"

void			cb_draw_frame(t_cbdata *cb)
{
	cb_print_floor_and_ceilling(cb);
	cb_draw_walls(cb);
	cb_draw_sprites(cb);
}
