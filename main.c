/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 23:06:43 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/26 16:01:35 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
#include <wchar.h>

void			print_struct(t_printf *specs)
{
	printf("iszero: %d\n", specs->iszero);
	printf("isspace: %d\n", specs->isspace);
	printf("ishash: %d\n", specs->ishash);
	printf("isminus: %d\n", specs->isminus);
	printf("isplus: %d\n", specs->isplus);
	printf("width: %d\n", specs->width);
	printf("precision: %d\n", specs->precision);
	printf("ishh: %d\n", specs->ishh);
	printf("ish: %d\n", specs->ish);
	printf("isll: %d\n", specs->isll);
	printf("isl: %d\n", specs->isl);
	printf("isj: %d\n", specs->isj);
	printf("isz: %d\n", specs->isz);
	printf("converter: %c\n", specs->converter);
	printf("negative: %d\n", specs->negative);
	printf("printed: %d\n", specs->printed);
}

int		main()
{
	int res = 0;
	int re2 = 0;

	res = ft_printf("%15.4d", -424242);
	printf("\nResult: %d\n", res);
//	re2 = printf("%+c", 48);
	re2 = printf("%15.4d", -424242);
	printf("\nResult: %d\n", re2);
/*	printf("\nResult: %d\n", ft_printf("[%5p]\n", 0));
	ft_printf("%");
	printf("\n");
	printf("%");
	while (1);
*/
	return (0);
}
