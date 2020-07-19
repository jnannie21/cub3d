/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 14:52:39 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 22:11:03 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_num(int n)
{
	int		num;

	num = 1;
	while (n / ft_pow10(num) != 0)
		num++;
	return (num);
}

void			ft_putnbr_fd(int n, int fd)
{
	int		num;

	num = count_num(n);
	if (n >= 0)
		n *= (-1);
	else
		ft_putchar_fd('-', fd);
	while (num--)
		ft_putchar_fd((-1) * ((int)(n / ft_pow10(num)) % 10 - 48), fd);
}
