/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 12:35:42 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/14 18:47:03 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** when little == "\0", even if len == 0, that's why if (len == 0) so low
*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len && little[i] != '\0' && little[i] == big[i])
		i++;
	if (little[i] == '\0')
		return ((char *)big);
	if (len == 0)
		return (0);
	return (ft_strnstr(big + 1, little, len - 1));
}
