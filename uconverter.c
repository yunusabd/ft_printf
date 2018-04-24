/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:18:55 by yabdulha          #+#    #+#             */
/*   Updated: 2018/03/19 21:38:05 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static long long		convert_len(va_list ap, const t_printf *specs)
{
	if (specs->isll == 1)
		return ((unsigned long long)va_arg(ap, long long));
	if (specs->isl == 1 || specs->converter == 'U' ||
			specs->converter == 'O')
		return ((unsigned long)va_arg(ap, long));
	if (specs->ishh == 1)
		return ((unsigned char)va_arg(ap, int));
	if (specs->ish == 1)
		return ((unsigned short)va_arg(ap, int));
	if (specs->isj == 1)
		return ((uintmax_t)va_arg(ap, uintmax_t));
	if (specs->isz)
		return ((size_t)va_arg(ap, size_t));
	return ((unsigned int)va_arg(ap, int));
}

char					*convert_u(va_list ap, t_printf *specs)
{
	long long		nb;
	char			*ret;

	nb = convert_len(ap, specs);
	specs->negative = 0;
	specs->isplus = 0;
	ret = ft_itoa_base_u(nb, 10);
	ret = padding(ret, specs);
	return (ret);
}

char					*convert_x(va_list ap, t_printf *specs)
{
	long long	nb;
	char		*ret;
	char		*ptr;

	nb = convert_len(ap, specs);
	specs->negative = 0;
	specs->isplus = 0;
	ret = ft_itoa_base_u(nb, 16);
	if (specs->converter == 'x' || specs->converter == 'X')
	{
		if (specs->ishash && nb != 0)
			ret = ft_strjoinfree("0X", ret, 2);
	}
	if (specs->precision == 0)
	{
		free(ret);
		ret = ft_strdup("");
	}
	ptr = padding(ret, specs);
	if (specs->ishash && ptr[1] == '0')
	{
		*(ft_strchr(ptr, 'X')) = '0';
		ptr[1] = 'X';
	}
	if (specs->converter == 'x')
		return (ft_strmap_p(ptr, ft_tolowercase));
	return (ptr);
}

char					*convert_o(va_list ap, t_printf *specs)
{
	long long	nb;
	char		*ret;

	if (specs->precision == 0)
		ret = ft_strdup("");
	else
	{
		nb = convert_len(ap, specs);
		ret = ft_itoa_base_u(nb, 8);
	}
	if ((specs->converter == 'o' || specs->converter == 'O')
			&& (specs->ishash && (nb != 0 || specs->precision == 0)))
		ret = ft_strjoinfree("0", ret, 2);
	ret = padding(ret, specs);
	return (ret);
}
