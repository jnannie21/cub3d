/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 20:57:39 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/06 21:45:20 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_strspn(const char *s, const char *accept)
{
	size_t		i;

	i = 0;
	while (s[i])
		if (ft_strchr(accept, s[i]))
			i++;
		else
			break ;
	return (i);
}
