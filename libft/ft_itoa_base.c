/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:10:46 by yabdulha          #+#    #+#             */
/*   Updated: 2018/03/05 02:33:21 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int value, int base)
{
	char	*buff;
	char	*digits;
	int		len;
	int		minus;

	if (base < 2 || base > 16)
		return (NULL);
	minus = (value < 0 && base == 10) ? 1 : 0;
	value *= (value < 0) ? -1 : 1;
	len = ft_numlen(value, base) + minus;
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
