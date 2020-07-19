/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 11:41:09 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/12 14:08:32 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l;

	if (lst == 0 || del == 0)
		return ;
	while (*lst)
	{
		l = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(l, del);
	}
}
