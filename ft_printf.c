/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 20:44:26 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/30 18:20:22 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

#include <wchar.h>

int			print_arg(va_list ap, t_printf *specs, char *s, int count)
{
	if (specs->converter == '%')
		s = handle_percent(specs);
	else if (specs->converter == 'p')
		s = convert_p(ap, specs);
	else if (specs->converter == 'x' || specs->converter == 'X')
		s = convert_x(ap, specs);
	else if (specs->converter == 'o' || specs->converter == 'O')
		s = convert_o(ap, specs);
	else if (specs->converter == 'd' || specs->converter == 'i')
		s = init_d(ap, specs);
	else if (specs->converter == 'u' || specs->converter == 'U')
		s = convert_u(ap, specs);
	else if (specs->converter == 'c' || specs->converter == 'C')
	{
		s = convert_c(ap, specs);
		if (s == NULL)
			return (empty_string(s, specs, count));
	}
	else if (specs->converter == 's' || specs->converter == 'S')
		s = init_s(ap, specs);
	else if ((specs->width)--)
		s = padding(ft_strdup(""), specs);
	count += ft_putstr(s);
	free(s);
	return (count);
}

int			ft_printf(char *format, ...)
{
	va_list		ap;
	int			i;
	t_printf	new;
	int			ret;
	char		*tmp;

	setlocale(LC_ALL, "");
	va_start(ap, format);
	ret = 0;
	i = 0;
	tmp = ft_strnew(BUFFSIZE);
	while (*format)
	{
		while (i < BUFFSIZE && *format && *format != '%')
		{
			tmp[i] = *format;
			i++;
			format++;
			ret++;
		}
		if (i)
			write(1, tmp, i);
		ft_bzero((void*)tmp, i);
		i = 0;
		if (*format == '%')
		{
			ft_memset(&new, 0, sizeof(t_printf));
			format = parse_spec(format, &new);
			ret += print_arg(ap, &new, NULL, 0);
		}
	}
	if (i)
		write(1, tmp, i);
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
