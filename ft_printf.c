/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 20:44:26 by yabdulha          #+#    #+#             */
/*   Updated: 2018/03/08 17:05:32 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

#include <wchar.h>

int		print_arg(va_list ap, t_printf *specs)
{
	int		d;
	char	*s;
	char	*tmp;
	int		count;

	count = 0;
	if (specs->converter == 'd')
		d = va_arg(ap, int);
	if (specs->converter == 's')
	{
		s = va_arg(ap, char*);
		if (specs->width == -1)
			count += ft_putstr(s);
		else
		{
			tmp = ft_strnew(specs->width - ft_strlen(s));
			tmp = ft_memset((void*)tmp, ' ', (specs->width - ft_strlen(s)));
			if (specs->isminus)
				s = ft_strjoin(s, tmp);
			else
				s = ft_strjoin(tmp, s);
			while (specs->precision-- != 0 && *s)
			{
				ft_putchar(*s++);
				count++;
			}
		}
	}
	return (count);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	t_printf	new;

	va_start(ap, format);
	new.printed = 0;
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar(*format);
			format++;
			new.printed++;
		}
		else 
		{
			format = parse_spec(format, &new);
			new.printed = print_arg(ap, &new);
		}
	}
	va_end(ap);
	return (new.printed);
}

size_t		ft_wchar_len(wchar_t wc)
{
	if ((int)wc >= 0 && (int)wc <= 0x7F)
		return (1);
	else if ((int)wc <= 0x7FF)
		return (2);
	else if ((int)wc <= 0xFFFF)
		return (3);
	else if ((int)wc <= 0x10FFFF)
		return (4);
	return (0);
}
