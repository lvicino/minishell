/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:08:51 by lvicino           #+#    #+#             */
/*   Updated: 2023/11/20 17:41:45 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tab_d;
	unsigned char	*tab_s;

	if (!dest && !src)
		return (NULL);
	tab_d = (unsigned char *)dest;
	tab_s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		tab_d[i] = tab_s[i];
		i++;
	}
	return (dest);
}
