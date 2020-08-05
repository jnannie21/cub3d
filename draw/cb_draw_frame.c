/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_draw_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 21:49:44 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/05 20:17:03 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cb_cub3d.h"

void			cb_draw_frame(t_cbdata *cb)
{
	cb_print_floor_and_ceilling(cb);
	cb_draw_walls(cb);
	cb_draw_sprites(cb);
}
