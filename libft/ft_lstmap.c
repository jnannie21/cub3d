/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 15:30:20 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/13 17:13:43 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*newlist;
	t_list		*newel;
	void		*new_content;

	if (f == 0 || del == 0)
		return (0);
	newlist = 0;
	while (lst)
	{
		new_content = f(lst->content);
		newel = ft_lstnew(new_content);
		if (newel == 0 || new_content == 0)
		{
			ft_lstclear(&newlist, del);
			return (0);
		}
		ft_lstadd_back(&newlist, newel);
		lst = lst->next;
	}
	return (newlist);
}
