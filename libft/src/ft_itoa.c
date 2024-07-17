/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:35:51 by lvicino           #+#    #+#             */
/*   Updated: 2023/11/20 17:40:59 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_itoa_aux(char *str, size_t i, long nb)
{
	if (nb < 0)
	{
		nb *= -1;
		str[0] = '-';
	}
	while (nb != 0)
	{
		str[i] = (nb % 10) + '0';
		nb /= 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	long	nb;
	size_t	ln;
	char	*str;

	nb = n;
	ln = 0;
	if (nb <= 0)
		ln++;
	while (nb != 0)
	{
		ln++;
		nb /= 10;
	}
	nb = n;
	str = malloc(sizeof(char) * (ln + 1));
	if (!str)
		return (NULL);
	str[ln] = 0;
	if (nb == 0)
		str[0] = '0';
	else
		ft_itoa_aux(str, ln - 1, nb);
	return (str);
}
