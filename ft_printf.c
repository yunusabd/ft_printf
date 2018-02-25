/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 20:44:26 by yabdulha          #+#    #+#             */
/*   Updated: 2018/02/25 15:29:31 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <wchar.h>

int		print_arg(va_list ap, t_printf *specs)
{
	int		d;
	char	*s;
	char	*tmp;

	if (specs->converter == 'd')
	{
		d = va_arg(ap, int);
		printf("[%d]", d);
	}
	if (specs->converter == 's')
	{
		s = va_arg(ap, char*);
		if (specs->width > ft_strlen(s))
		{
			tmp = ft_strnew(specs->width - ft_strlen(s));
			tmp = ft_memset((void*)tmp, ' ', (specs->width - ft_strlen(s)));
			if (specs->isminus)
				s = ft_strjoin(s, tmp);
			else
				s = ft_strjoin(tmp, s);
		}
		while (specs->precision-- != 0 && *s)
			ft_putchar(*s++);
	}
	return (0);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	t_printf	new;

	va_start(ap, format);
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar(*format);
			format++;
		}
		else 
		{
			format = parse_spec(format, &new);
			print_arg(ap, &new);
		}
	}
	va_end(ap);
	return (1);
}

int		main()
{
	char		*str = "中文";
	int			myiny = 42;
	char		c = 'a';
	char		*ptr;
	wchar_t		*wc = L"蹩鎞";
	const wchar_t me = 0x1F378;


	//printf("%.s", "popo");
	//ft_printf("ft_printf string:\n[%#10.2.11s]", str);
	printf("\nprintf string:\n[%ls]", wc);
	return (0);
}
