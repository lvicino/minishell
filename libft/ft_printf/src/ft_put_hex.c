/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:14:54 by lvicino           #+#    #+#             */
/*   Updated: 2024/01/03 16:40:31 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_ulhex(unsigned long nb, int *ln)
{
	char	*base;
	char	c;

	base = "0123456789abcdef";
	if (nb > 15)
		ft_put_ulhex(nb / 16, ln);
	c = base[nb % 16];
	*ln += write(1, &c, 1);
	return ;
}

void	ft_put_uuhex(unsigned int nb, int *ln)
{
	char	*base;
	char	c;

	base = "0123456789ABCDEF";
	if (nb > 15)
		ft_put_uuhex(nb / 16, ln);
	c = base[nb % 16];
	*ln += write(1, &c, 1);
	return ;
}

void	ft_put_ptr(void *ptr, int *ln)
{
	if (!ptr)
		*ln += write(1, "(nil)", 5);
	else
	{
		*ln += write(1, "0x", 2);
		ft_put_ulhex((unsigned long)ptr, ln);
	}
	return ;
}
