/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor < agungor@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:00:59 by agungor           #+#    #+#             */
/*   Updated: 2023/10/31 15:47:38 by agungor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar(char c, t_printf *prnt)
{
	return (prnt->lenght++, write(1, &c, 1));
}

static int	ft_putstr(char *s, t_printf *prnt)
{
	if (!s)
		s = "(null)";
	while (*s)
	{
		if (ft_putchar(*s, prnt) == -1)
			return (-1);
		return (1);
	}
}

static int	ft_format(t_printf *prnt)
{
	if (prnt->frmt == '%')
		return (ft_putchar('%', prnt));
	else if (prnt->frmt == 'c')
		return (ft_putchar(va_arg(prnt->args, char), prnt));
	else if (prnt->frmt == 's')
		return (ft_putstr(va_arg(prnt->args, char *), prnt));
	else if (prnt->frmt == 'd' || prnt->frmt == 'i')
		return (ft_itoa_base(va_arg(prnt->args, int), DEC, 10, prnt));
	else if (prnt->frmt == 'u')
		return (ft_itoa_base(va_arg(prnt->args, unsigned int), DEC, 10, prnt));
	else if (prnt->frmt == 'x')
		return (ft_itoa_base(va_arg(prnt->args, unsigned int), HEXLOW, 16,
				prnt));
	else if (prnt->frmt == 'X')
		return (ft_itoa_base(va_arg(prnt->args, unsigned int), HEXUP, 16,
				prnt));
	else if (prnt->frmt == 'p')
		return (ft_itoa_base(va_arg(prnt->args, u_int64_t), HEXLOW, 16, prnt));
	return (-1);
}

int	ft_printf(const char *s, ...)
{
	t_printf	prnt;

	prnt.lenght = 0;
	va_start(prnt.args, s);
	while (*s)
	{
		if (*s == '%')
		{
			prnt.frmt = *++s;
			if (ft_format(&prnt) == -1)
				return (-1);
		}
		else if (ft_putchar(*s, &prnt) == -1)
			return (-1);
		s++;
	}
	return (va_end(prnt.args), prnt.lenght);
}
