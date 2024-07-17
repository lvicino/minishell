/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:06:45 by lvicino           #+#    #+#             */
/*   Updated: 2023/12/13 14:09:18 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_unbr_aux(unsigned long nb, int *ln)
{
	char	c;

	if (nb > 9)
		ft_put_unbr_aux(nb / 10, ln);
	c = (nb % 10) + '0';
	*ln += write (1, &c, 1);
	return ;
}

void	ft_put_unbr(unsigned int n, int *ln)
{
	unsigned long	nb;

	nb = n;
	if (nb == 0)
		*ln += write(1, "0", 1);
	else
		ft_put_unbr_aux(nb, ln);
	return ;
}
