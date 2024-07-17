/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:27:54 by lvicino           #+#    #+#             */
/*   Updated: 2024/01/30 14:49:45 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *fmt, ...);
void	ft_put_unbr(unsigned int n, int *ln);
void	ft_put_ulhex(unsigned long nb, int *ln);
void	ft_put_uuhex(unsigned int nb, int *ln);
void	ft_put_ptr(void *ptr, int *ln);

void	ft_printf_putchar(char c, int *ln);
void	ft_printf_putstr(char *s, int *ln);
void	ft_printf_putnbr(int n, int *ln);

size_t	ft_strlen(const char *s);

#endif
