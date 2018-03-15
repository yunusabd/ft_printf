/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_max.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 21:59:32 by yabdulha          #+#    #+#             */
/*   Updated: 2018/03/14 12:46:47 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base_max(intmax_t value, int base)
{
	char	*buff;
	char	*digits;
	int		len;
	int		minus;
	int		tmp;

	if (base < 2 || base > 16)
		return (NULL);
	minus = (value < 0 && base == 10) ? 1 : 0;
	len = ft_numlen_max(value, base) - minus;
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
	if (minus)
		buff = ft_strjoin("-", buff);
	return (buff);
}
