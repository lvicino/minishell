/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:02:25 by lvicino           #+#    #+#             */
/*   Updated: 2024/01/08 19:37:53 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*join_line(char *str, t_data *get, int fd)
{
	char	*stash;
	int		j;
	int		k;

	j = 0;
	k = 0;
	get->stash_ln[fd] += (get->i[fd] - get->start[fd]);
	stash = (char *)malloc(sizeof(char) * (get->stash_ln[fd] + 1));
	if (!stash)
		return (free(str), NULL);
	stash[get->stash_ln[fd]] = 0;
	while (str && str[j])
	{
		stash[j] = str[j];
		j++;
	}
	if (str)
		free(str);
	while (k < (get->i[fd] - get->start[fd]))
	{
		stash[j + k] = get->buffer[fd][get->start[fd] + k];
		k++;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static t_data	get;

	get.str = NULL;
	if (fd >= 0 && !get.start[fd])
		get.ln[fd] = read(fd, get.buffer[fd], BUFFER_SIZE);
	while (fd >= 0 && get.buffer[fd][get.i[fd]] != '\n' && get.ln[fd] > 0)
	{
		get.i[fd]++;
		if (get.i[fd] == get.ln[fd])
		{
			get.str = join_line(get.str, &get, fd);
			get.i[fd] = 0;
			get.start[fd] = 0;
			get.ln[fd] = read(fd, get.buffer[fd], BUFFER_SIZE);
		}
	}
	if (get.ln[fd] > 0)
	{
		get.i[fd]++;
		get.str = join_line(get.str, &get, fd);
		get.i[fd] %= get.ln[fd];
		get.start[fd] = get.i[fd];
		get.stash_ln[fd] = 0;
	}
	return (get.str);
}
