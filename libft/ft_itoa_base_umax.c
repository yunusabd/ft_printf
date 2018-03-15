/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_umax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:43:56 by yabdulha          #+#    #+#             */
/*   Updated: 2018/03/14 12:45:51 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base_umax(uintmax_t value, int base)
{
	char	*buff;
	char	*digits;
	int		len;
	int		tmp;

	if (base < 2 || base > 16)
		return (NULL);
	len = ft_numlen_umax(value, base);
	tmp = ABS(value % base);
	value /= base;
	value = ABS(value);
	buff = ft_strnew(len);
	digits = "0123456789ABCDEF";
	buff[len - 1] = digits[tmp];
	while (--len && value)
	{
		buff[len - 1] = digits[value % base];
		value /= base;
	}
	return (buff);
}
