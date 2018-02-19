/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 20:25:10 by yabdulha          #+#    #+#             */
/*   Updated: 2017/11/20 21:02:06 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	i;
	int	negative;
	int	result;

	i = 0;
	result = 0;
	negative = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\r' || str[i] == '\f')
		i++;
	if ((str[i] == '-' || str[i] == '+'))
	{
		negative = (str[i] == '-') ? 1 : 0;
		i++;
	}
	if (!(ft_isdigit(str[i])))
		return (0);
	while (ft_isdigit(str[i]) == 1)
	{
		result = (result * 10 - (str[i] - '0'));
		i++;
	}
	if (!negative)
		result = -result;
	return (result);
}
