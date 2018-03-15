/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:18:55 by yabdulha          #+#    #+#             */
/*   Updated: 2018/03/14 18:34:11 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static uintmax_t		convert_len(va_list ap, t_printf *specs)
{
	intmax_t	nb;

	if (specs->converter == 'U')
		nb = (unsigned long int)va_arg(ap, unsigned long int);
	else if (specs->ishh == 1)
		nb = (unsigned char)va_arg(ap, int);
	else if (specs->ish == 1)
		nb = (unsigned short int)va_arg(ap, int);
	else if (specs->isll == 1)
		nb = (unsigned long long int)va_arg(ap, unsigned long long int);
	else if (specs->isl == 1)
		nb = (unsigned long int)va_arg(ap, unsigned long int);
	else if (specs->isj == 1)
		nb = (uintmax_t)va_arg(ap, uintmax_t);
	else if (specs->isz)
		nb = (size_t)va_arg(ap, size_t);
	else
		nb = (unsigned int)va_arg(ap, unsigned int);
	return (nb);
}

char					*convert_u(va_list ap, t_printf *specs)
{
	uintmax_t		nb;
	char			*ret;

	nb = (uintmax_t)convert_len(ap, specs);
	specs->negative = 0;
	specs->isplus = 0;
	ret = ft_itoa_base_max((intmax_t)nb, 10);
	ret = padding(ret, specs);
	return (ret);
}

char					*convert_x(va_list ap, t_printf *specs)
{
	uintmax_t	nb;
	char		*ret;
	char		*ptr;

	nb = convert_len(ap, specs);
	specs->negative = 0;
	specs->isplus = 0;
	ret = ft_itoa_base_umax(nb, 16);
	if (specs->converter == 'x' || specs->converter == 'X')
	{
		if (specs->ishash && nb != 0)
			ret = ft_strjoin("0X", ret);
	}
	if (specs->precision == 0)
		ret = "";
	ret = padding(ret, specs);
	if (specs->ishash && ret[1] == '0')
	{
		*(ft_strchr(ret, 'X')) = '0';
		ret[1] = 'X';
	}
	if (specs->converter == 'x')
		ret = ft_strmap(ret, ft_tolowercase);
	return (ret);
}

char					*convert_o(va_list ap, t_printf *specs)
{
	uintmax_t	nb;
	char		*ret;

	nb = convert_len(ap, specs);
	specs->negative = 0;
	specs->isplus = 0;
	ret = ft_itoa_base_umax(nb, 8);
	if (specs->precision == 0)
		ret = "";
	if (specs->converter == 'o' || specs->converter == 'O')
	{
		if (specs->ishash && (nb != 0 || specs->precision == 0))
			ret = ft_strjoin("0", ret);
	}
	ret = padding(ret, specs);
	return (ret);
}
