/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:02:25 by lvicino           #+#    #+#             */
/*   Updated: 2024/03/26 18:31:36 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_line(char *str, t_data *get)
{
	char	*stash;
	int		j;
	int		k;

	j = 0;
	k = 0;
	get->stash_ln += (get->i - get->start);
	stash = (char *)malloc(sizeof(char) * (get->stash_ln + 1));
	if (!stash)
		return (free(str), NULL);
	stash[get->stash_ln] = 0;
	while (str && str[j])
	{
		stash[j] = str[j];
		j++;
	}
	if (str)
		free(str);
	while (k < (get->i - get->start))
	{
		stash[j + k] = get->buffer[get->start + k];
		k++;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static t_data	get;

	get.str = NULL;
	if (fd >= 0 && !get.start)
		get.ln = read(fd, get.buffer, BUFFER_SIZE);
	while (fd >= 0 && get.buffer[get.i] != '\n' && get.ln > 0)
	{
		get.i++;
		if (get.i == get.ln)
		{
			get.str = join_line(get.str, &get);
			get.i = 0;
			get.start = 0;
			get.ln = read(fd, get.buffer, BUFFER_SIZE);
		}
	}
	if (get.ln > 0)
	{
		get.i++;
		get.str = join_line(get.str, &get);
		get.i %= get.ln;
		get.start = get.i;
		get.stash_ln = 0;
	}
	return (get.str);
}
