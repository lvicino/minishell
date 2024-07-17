/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:07:02 by lvicino           #+#    #+#             */
/*   Updated: 2024/04/22 14:38:00 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	ln;
	size_t	i;

	if (!s)
		return (NULL);
	ln = ft_strlen(s);
	i = 0;
	str = malloc(sizeof(char) * (ln + 1));
	if (!str)
		return (NULL);
	str[ln] = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}
