/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:39:00 by lvicino           #+#    #+#             */
/*   Updated: 2023/11/20 17:42:35 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	size_t			ln;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	ln = ft_strlen(s);
	str = malloc(sizeof(char) * (ln + 1));
	if (!str)
		return (NULL);
	str[ln] = 0;
	while (i < ln)
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	return (str);
}
