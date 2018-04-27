/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 21:10:54 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/27 19:20:43 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static char	*handle_precision(char *str, t_printf *specs)
{
	char	*tmp;
	int		diff;

	if (specs->precision == 0)
		return (ft_strdup(""));
	diff = specs->precision - ft_strlen(str);
	if ((specs->isplus || specs->negative) && specs->negative)
		specs->isplus = 0;
	tmp = ft_strnew(diff);
	tmp = ft_memset((void*)tmp, '0', diff);
	return (ft_strjoinfree(tmp, str, 3));
}

static char	*handle_width(char *str, t_printf *specs)
{
	char	*tmp;
	char	fill;
	int		diff;
	char	*ret;

	diff = specs->width - ft_strlen(str);
	fill = (specs->iszero == 1 && !specs->isminus) ? '0' : ' ';
	diff -= (specs->negative || specs->isplus) ? 1 : 0;
	tmp = ft_strnew(diff);
	tmp = ft_memset((void*)tmp, fill, diff);
	if (specs->isminus)
		return (ft_strjoinfree(str, tmp, 3));
	else
		return (ft_strjoinfree(tmp, str, 3));
}

static char	*add_sign(char *str, t_printf *specs)
{
	char	sign;
	int		i;

	i = 0;
	if (specs->converter == 'c' || specs->converter == 'C')
		return (str);
	sign = (specs->negative) ? '-' : '+';
	if (specs->negative || specs->isplus)
		str = ft_strjoinfree(" ", str, 2);
	while (str[i + 1] == ' ')
		i++;
	str[i] = sign;
	return (str);
}

char		*padding(char *str, t_printf *specs)
{
	char	sign;

	if (!str)
		return (NULL);
	if (specs->width > specs->precision && ft_strlen(str) < specs->precision &&
			specs->isminus == 1 && specs->precision > 0)
		specs->width++;
	if (specs->precision > 0 && specs->precision > ft_strlen(str))
		str = handle_precision(str, specs);
	if (specs->width > 0 && specs->width > ft_strlen(str))
		str = handle_width(str, specs);
	if (specs->isplus || specs->negative)
		str = add_sign(str, specs);
	if (specs->precision > 0 && specs->width > 0 &&
			specs->width > specs->precision && ft_strlen(str) >= specs->width &&
			specs->isminus)
		str[ft_strlen(str) - 1] = '\0';
	return (str);
}
