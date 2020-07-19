/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 08:44:16 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/08 11:47:19 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	mem_size;

	mem_size = nmemb * size;
	mem = malloc(mem_size);
	if (mem == 0)
		return (0);
	while (mem_size--)
		((char *)mem)[mem_size] = '\0';
	return (mem);
}
