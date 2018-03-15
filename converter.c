/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:18:55 by yabdulha          #+#    #+#             */
/*   Updated: 2018/03/15 14:58:23 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

char			*convert_s(char *str, t_printf *specs)
{
	char	*ret;
	char	*tmp;
	char	fill;
	int		len;

	if (specs->precision == 0)
		ret = "";
	else if (specs->precision > 0)
		ret = strndup(str, specs->precision);
	else
		ret = str;
	if (specs->width > 0 && specs->width > ft_strlen(ret))
	{
		len = specs->width - ft_strlen(ret);
		len = (specs->negative) ? (len - 1) : (len);
		tmp = (char*)malloc(sizeof(*ret) * (len));
		fill = (specs->iszero == 1 && !specs->isminus) ? '0' : ' ';
		tmp = ft_memset((void*)tmp, fill, len);
		if (specs->isminus)
			ret = ft_strjoin(ret, tmp);
		else
			ret = ft_strjoin(tmp, ret);
		free(tmp);
	}
	return (ret);
}

char			*convert_c(va_list ap, t_printf *specs)
{
	wchar_t	c;
	char	*ret;

	if (specs->converter == 'C' || specs->isl)
		c = va_arg(ap, wchar_t);
	else
		c = va_arg(ap, int);
	ret = ft_strnew(1);
	ret[0] = c;
	if (c == 0)
		ret = NULL;
	ret = padding(ret, specs);
	return (ret);
}

/*
** Converts the length of d and i.
*/

static intmax_t	convert_len(va_list ap, t_printf *specs)
{
	intmax_t	nb;

	if (specs->ishh == 1)
		nb = (signed char)(va_arg(ap, int));
	else if (specs->ish == 1)
		nb = (short)(va_arg(ap, int));
	else if (specs->isll == 1)
		nb = (long long)(va_arg(ap, long long int));
	else if (specs->isl == 1)
		nb = (long)(va_arg(ap, long));
	else if (specs->isj == 1)
		nb = (intmax_t)(va_arg(ap, intmax_t));
	else if (specs->isz == 1)
		nb = (size_t)(va_arg(ap, size_t));
	else
		nb = (int)(va_arg(ap, int));
	nb = (intmax_t)nb;
	return (nb);
}

char			*convert_p(va_list ap, t_printf *specs)
{
	char			*ret;
	intmax_t		nb;

	nb = va_arg(ap, intmax_t);
	ret = ft_itoa_base_max(nb, 16);
	ret = ft_strjoin("0x", ret);
	ret = ft_strmap(ret, ft_tolowercase);
	return (ret);
}

char			*convert_d(va_list ap, t_printf *specs)
{
	char			*ret;
	intmax_t		nb;

	nb = convert_len(ap, specs);
	specs->negative = (nb < 0) ? 1 : 0;
	nb < 0 ? nb = -nb : 0;
	if (!(specs->isl || specs->isll || specs->isj)
			&& (nb == 2147483648 || nb == -2147483648))
		return ("-2147483648");
	if (specs->isll || specs->isl || specs->isj || specs->isz)
		ret = ft_itoa_base_max(nb, 10);
	else
		ret = ft_itoa_base(nb, 10);
	if (ft_strchr(ret, '-'))
		specs->negative = 0;
	if (specs->precision == 0 && nb == 0)
		ret = "";
	ret = padding(ret, specs);
	if (!specs->negative && !specs->isplus && specs->isspace
			&& ft_atoi(ret) > 0)
		ret = ft_strjoin((ret[0] != ' ') ? " " : "", ret);
	return (ret);
}
