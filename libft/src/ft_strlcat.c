/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:16:27 by lvicino           #+#    #+#             */
/*   Updated: 2023/11/20 17:42:16 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	ln_dest;
	size_t	ln_src;

	if ((!dest || !src) && size == 0)
		return (0);
	i = 0;
	j = 0;
	ln_dest = ft_strlen(dest);
	ln_src = ft_strlen(src);
	while (dest[i] && i < size)
		i++;
	if (size == 0 || i == size)
		return (size + ln_src);
	while (j < size - ln_dest - 1 && src[j])
		dest[i++] = src[j++];
	dest[i] = 0;
	return (ln_dest + ln_src);
}
