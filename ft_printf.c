/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agungor < agungor@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:00:59 by agungor           #+#    #+#             */
/*   Updated: 2023/11/01 11:26:21 by agungor          ###   ########.fr       */
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
	}
	return (1);
}

static int	ft_itoa_base(u_int64_t n, char *s, int base, t_printf *prnt)
{
	char	mod;
	int		str_num[30]; // U_INT64_T MAX =  18,446,744,073,709,551,615 bir dizide tuttuğumuzda maksimum bu dizi 21 elemanlı olmalı  10 tabanında 16 lık tabanda zaten basamak sayısı daha küçük oluyor. 
	int		i;

	i = 0;
	mod = (prnt->frmt == 'i' || prnt->frmt == 'd') + 2 * (prnt->frmt == 'p');
	if (mod == 1 && (int)n < 0)
	{
		n = -n;
		if (ft_putchar('-', prnt) == -1)
			return (-1);
	}
	else if (mod == 2 && ft_putstr("0x", prnt) == -1)
		return (-1);
	else if (!n && ft_putchar('0', prnt) == -1)
		return (-1);
	while (n)
	{
		str_num[i] = n % base + 48;
		n /= base;
	}
	while (i--)
		if (ft_putchar(s[str_num[i]], prnt) == -1)
			return (-1);
	return (1);
}

static int	ft_format(t_printf *prnt)
{
	if (prnt->frmt == '%')
		return (ft_putchar('%', prnt));
	else if (prnt->frmt == 'c')
		return (ft_putchar(va_arg(prnt->args, int), prnt));
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
