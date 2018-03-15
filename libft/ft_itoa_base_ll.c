/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 21:18:41 by yabdulha          #+#    #+#             */
/*   Updated: 2018/03/11 21:20:24 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base_ll(long long value, int base)
{
	char	*buff;
	char	*digits;
	int		len;
	int		minus;

	if (base < 2 || base > 16)
		return (NULL);
	minus = (value < 0 && base == 10) ? 1 : 0;
	value *= (value < 0) ? -1 : 1;
	len = ft_numlen_ll(value, base) + minus;
	buff = ft_strnew(len);
	digits = "0123456789ABCDEF";
	while (len--)
	{
		buff[len] = digits[value % base];
		value /= base;
	}
	if (minus)
		buff[0] = '-';
	return (buff);
}
