/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:06:03 by lvicino           #+#    #+#             */
/*   Updated: 2023/11/20 17:42:48 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strtrim_start(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (s1[i] && set[j])
	{
		if (s1[i] == set[j])
		{
			n++;
			j = 0;
			i++;
		}
		else
			j++;
	}
	return (n);
}

static int	ft_strtrim_end(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	n;

	j = 0;
	n = 0;
	i = ft_strlen(s1) - 1;
	while (i >= ft_strtrim_start(s1, set) && set[j])
	{
		if (set[j] == s1[i])
		{
			n++;
			j = 0;
			i--;
		}
		else
			j++;
	}
	return (n);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = ft_strtrim_start(s1, set);
	end = ft_strtrim_end(s1, set);
	str = ft_substr(s1, start, ft_strlen(s1) - (start + end));
	return (str);
}
