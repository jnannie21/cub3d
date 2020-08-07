/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_print_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 21:49:03 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/07 11:55:00 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cb_cub3d_bonus.h"

void		cb_print_map(char **map)
{
	while (*map)
	{
		write(1, *map, ft_strlen(*map));
		write(1, "\n", 1);
		map++;
	}
}
