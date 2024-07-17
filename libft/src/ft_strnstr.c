/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:17:23 by lvicino           #+#    #+#             */
/*   Updated: 2023/11/20 17:42:41 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!little[0])
		return ((char *)big);
	i = 0;
	j = 0;
	while (i + j < len && big[i + j])
	{
		if (big[i + j] == little[j])
		{
			j++;
			if (!little[j])
				return ((char *)big + i);
		}
		else
		{
			i++;
			j = 0;
		}
	}
	return (NULL);
}
