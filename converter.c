/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:18:55 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/24 17:29:13 by yabdulha         ###   ########.fr       */
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
		str = ft_strdup("");
	else if (specs->precision > 0 && specs->precision < ft_strlen(str))
		str = ft_strndup(str, specs->precision);
	else
		str = ft_strdup(str);
	if (specs->width > 0 && specs->width > ft_strlen(str))
	{
		len = specs->width - ft_strlen(str);
		len = (specs->negative) ? (len - 1) : (len);
		tmp = ft_strnew(len);
		fill = (specs->iszero == 1 && !specs->isminus) ? '0' : ' ';
		tmp = ft_memset((void*)tmp, fill, len);
		if (specs->isminus)
			ret = ft_strjoinfree(str, tmp, 2);
		else
			ret = ft_strjoinfree(tmp, str, 1);
		str = ft_strdup(ret);
		free(ret);
	}
	return (str);
}

char			*convert_c(va_list ap, t_printf *specs)
{
	wchar_t	c;
	char	*ret;

	if (specs->converter == 'C' || specs->isl)
	{
		c = va_arg(ap, wchar_t);
		ret = handle_unicode(c);
		specs->isl = 1;
	}
	else
	{
		c = va_arg(ap, int);
		ret = ft_strnew(1);
		ret[0] = c;
	}
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
	ret = ft_itoa_base_u(nb, 16);
	ret = ft_strjoinfree("0x", ret, 2);
	ret = ft_strmap_p(ret, ft_tolowercase);
	return (ret);
}

char			*convert_d(va_list ap, t_printf *specs)
{
	char			*ret;
	intmax_t		nb;
	char			*tmp;

	nb = convert_len(ap, specs);
	specs->negative = (nb < 0) ? 1 : 0;
	nb < 0 ? nb = -nb : 0;
	if (!(specs->isl || specs->isll || specs->isj)
			&& (nb == 2147483648 || nb == -2147483648))
		return (ft_strdup("-2147483648"));
	ret = ft_itoa_base(nb, 10);
	if (ft_strchr(ret, '-'))
		specs->negative = 0;
	if (specs->precision == 0 && nb == 0)
	{
		free(ret);
		return (padding(ft_strdup(""), specs));
	}
	printf("\nret1: %p\n", ret);
	ret = padding(ret, specs);
	if (!specs->negative && !specs->isplus && specs->isspace
			&& ft_atoi(ret) > 0)
		ret = ft_strjoinfree((ret[0] != ' ') ? " " : "", ret, 2);
	printf("ret2: %p\n", ret);
	return (ret);
}
