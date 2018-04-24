/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 20:21:28 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/24 16:33:49 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_itoa_base(long long value, int base)
{
	char	*buff;
	char	*digits;
	int		len;
	int		tmp;
	int		minus;

	if (base < 2 || base > 16)
		return (NULL);
	minus = (value < 0) ? 1 : 0;
	len = ft_numlen_ll(value, base);
	tmp = value % base;
	tmp = ABS(tmp);
	value /= base;
	value = ABS(value);
	if (!(buff = ft_strnew(len)))
		return (NULL);
	digits = "0123456789ABCDEF";
	buff[len - 1] = digits[tmp];
	while (--len)
	{
		buff[len - 1] = digits[value % base];
		value /= base;
	}
	if (minus)
		buff[0] = '-';
	return (buff);
}
