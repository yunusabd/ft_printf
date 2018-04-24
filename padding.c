/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 21:10:54 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/24 17:48:54 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static char	*handle_precision(char *str, t_printf *specs, int pm)
{
	char	*tmp;
	int		diff;

	if (specs->precision == 0)
		return (ft_strdup(""));
	diff = specs->precision - ft_strlen(str);
	diff += (pm == 1 && ((specs->isplus && specs->isminus)
				|| specs->negative)) ? 1 : 0;
	tmp = ft_strnew(diff);
	tmp = ft_memset((void*)tmp, '0', diff);
	return (ft_strjoinfree(tmp, str, 3));
}

static char	*handle_width(char *str, t_printf *specs, int pm)
{
	char	*tmp;
	char	fill;
	int		diff;
	char	*ret;

	diff = specs->width - ft_strlen(str);
	fill = (specs->iszero == 1 && !specs->isminus) ? '0' : ' ';
	diff -= (specs->negative && specs->isminus && pm == 1) ? 1 : 0;
	tmp = ft_strnew(diff);
	tmp = ft_memset((void*)tmp, fill, diff);
	if (specs->isminus)
	{
		if (specs->negative)
			str = ft_strjoinfree(" ", str, 2);
		return (ft_strjoinfree(str, tmp, 2));
	}
	else
		return (ft_strjoinfree(tmp, str, 1));
	return (ret);
}

static char	*add_sign(char *str, t_printf *specs, int pm)
{
	char	sign;
	int		i;

	i = 0;
	sign = (specs->negative) ? '-' : '+';
	if (pm == 1)
		str = ft_strjoinfree(" ", str, 2);
	while (str[i + 1] == ' ')
		i++;
	str[i] = sign;
	return (str);
}

char		*padding(char *str, t_printf *specs)
{
	char	sign;
	int		pm;
	char	*tmp;

	if (!str)
		return (NULL);
	pm = (specs->isplus || specs->negative) ? 1 : 0;
	if (specs->precision > 0 && specs->precision > ft_strlen(str))
	{
		str = handle_precision(str, specs, pm--);
		specs->iszero = 0;
	}
	if (specs->width > 0 && specs->width > ft_strlen(str))
	{
		tmp = str;
		str = handle_width(str, specs, pm--);
		free(tmp);
		specs->iszero = 0;
	}
	if (specs->isplus || specs->negative)
		add_sign(str, specs, pm);
	return (str);
}
