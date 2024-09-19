/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:34:19 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/19 21:47:52 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tab_d;
	unsigned char	*tab_s;

	if (!dest && !src)
		return (NULL);
	tab_d = (unsigned char *)dest;
	tab_s = (unsigned char *)src;
	if (src > dest)
	{
		i = 0;
		while (i < n)
		{
			tab_d[i] = tab_s[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i-- > 0)
			tab_d[i] = tab_s[i];
	}
	return (dest);
}
