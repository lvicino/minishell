/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:39:30 by lvicino           #+#    #+#             */
/*   Updated: 2023/11/20 17:42:44 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = -1;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			j = i;
		i++;
	}
	if (str[i] == (unsigned char)c)
		j = i;
	if (j >= 0)
		return (str + j);
	return (NULL);
}
