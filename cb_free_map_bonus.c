/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_free_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 01:21:35 by jnannie           #+#    #+#             */
/*   Updated: 2020/08/07 11:51:25 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cb_cub3d_bonus.h"

void				cb_free_map(char **map)
{
	char	**temp_map;

	temp_map = map;
	if (temp_map)
		while (*temp_map)
		{
			free(*temp_map);
			temp_map++;
		}
	free(map);
}
