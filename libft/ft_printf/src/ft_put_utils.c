/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:06:45 by lvicino           #+#    #+#             */
/*   Updated: 2023/12/13 13:34:01 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_putnbr_aux(long nb, int *ln)
{
	char	c;

	if (nb > 9)
		ft_printf_putnbr_aux(nb / 10, ln);
	c = (nb % 10) + '0';
	*ln += write (1, &c, 1);
	return ;
}

void	ft_printf_putnbr(int n, int *ln)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		nb *= -1;
		*ln += write(1, "-", 1);
	}
	if (nb == 0)
		*ln += write(1, "0", 1);
	else
		ft_printf_putnbr_aux(nb, ln);
	return ;
}

void	ft_printf_putstr(char *s, int *ln)
{
	if (!s)
	{
		*ln += write(1, "(null)", 6);
		return ;
	}
	*ln += write(1, s, ft_strlen(s));
}

void	ft_printf_putchar(char c, int *ln)
{
	*ln += write(1, &c, 1);
}
