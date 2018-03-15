/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 20:44:26 by yabdulha          #+#    #+#             */
/*   Updated: 2018/03/15 17:33:44 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

#include <wchar.h>

int		print_arg(va_list ap, t_printf *specs)
{
	char			*s;
	int				count;

	count = 0;
	if (specs->converter == '%')
		s = padding("", specs);
	else if (specs->converter == 'p')
		s = convert_p(ap, specs);
	else if (specs->converter == 'x' || specs->converter == 'X')
		s = convert_x(ap, specs);
	else if (specs->converter == 'o' || specs->converter == 'O')
		s = convert_o(ap, specs);
	else if (specs->converter == 'd' || specs->converter == 'i')
		s = convert_d(ap, specs);
	else if (specs->converter == 'u' || specs->converter == 'U')
		s = convert_u(ap, specs);
	else if (specs->converter == 'c')
	{
		s = convert_c(ap, specs);
		if (s == NULL)
		{
			specs->precision = 0;
			specs->width--;
			s = padding("", specs);
			count += ft_putstr(s);
			ft_putchar('\0');
			return (count + 1);
		}
	}
	else if (specs->converter == 's')
	{
		s = va_arg(ap, char*);
		if (!s)
			s = ft_strdup("(null)");
		s = convert_s(s, specs);
	}
	count += ft_putstr(s);
	return (count);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	t_printf	new;
	int			ret;

	va_start(ap, format);
	ret = 0;
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar(*format);
			format++;
			ret++;
		}
		else 
		{
			format = parse_spec(format + 1, &new);
			ret += print_arg(ap, &new);
		}
	}
	va_end(ap);
	return (ret);
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
