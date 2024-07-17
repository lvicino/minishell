/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:14:54 by lvicino           #+#    #+#             */
/*   Updated: 2023/12/13 17:20:45 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_specifier(const char *fmt, va_list ap, int i, int *ln)
{
	if (fmt[i] == 'c')
		ft_printf_putchar(va_arg(ap, int), ln);
	else if (fmt[i] == 's')
		ft_printf_putstr(va_arg(ap, char *), ln);
	else if (fmt[i] == 'p')
		ft_put_ptr(va_arg(ap, void *), ln);
	else if (fmt[i] == 'd' || fmt[i] == 'i')
		ft_printf_putnbr(va_arg(ap, int), ln);
	else if (fmt[i] == 'u')
		ft_put_unbr(va_arg(ap, unsigned int), ln);
	else if (fmt[i] == 'x')
		ft_put_ulhex(va_arg(ap, unsigned int), ln);
	else if (fmt[i] == 'X')
		ft_put_uuhex(va_arg(ap, unsigned int), ln);
	else if (fmt[i] == '%')
		ft_printf_putchar('%', ln);
}

int	ft_printf(const char *fmt, ...)
{
	int		i;
	int		ln;
	va_list	ap;

	ln = 0;
	if (!fmt)
		return (-1);
	va_start(ap, fmt);
	i = -1;
	while (fmt[++i])
	{
		if (fmt[i] == '%')
		{
			check_specifier(fmt, ap, ++i, &ln);
		}
		else
			ft_printf_putchar(fmt[i], &ln);
	}
	va_end(ap);
	return (ln);
}
