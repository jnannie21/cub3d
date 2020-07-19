/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:27:18 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 21:30:58 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					*ft_fill_in(char *result, int pos,
								unsigned int length, char filler)
{
	char	*temp;

	if (length <= ft_strlen(result))
		return (result);
	temp = result;
	if (!(result = ft_calloc(length + 1, sizeof(char))))
		return (0);
	ft_memset(result, filler, length);
	ft_strcpytoend(result, temp + pos);
	ft_memcpy(result, temp, pos);
	free(temp);
	return (result);
}
