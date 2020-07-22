/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 09:39:21 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/22 09:43:02 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_strcspn(const char *s, const char *accept)
{
	size_t		i;

	i = 0;
	while (s[i])
		if (!ft_strchr(accept, s[i]))
			i++;
		else
			break ;
	return (i);
}
