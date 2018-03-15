/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 23:06:43 by yabdulha          #+#    #+#             */
/*   Updated: 2018/03/15 18:50:37 by yabdulha         ###   ########.fr       */
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
	char		*str = "中文";
	char		*this = "this";
	char		*string = "string";
	char		c = 'a';
	char		*ptr;
	wchar_t		*wc = L"蹩鎞";
	const wchar_t me = 0x1F378;
	int			res;

	res = ft_printf("%");
	printf("\nResult: %d\n", res);
	printf("\nResult: %d\n", printf("%"));
	printf("\n");
	//printf("\nprintf string:\n[%ls]", wc);
	//write(1, "[杯]\n", ft_wchar_len(L'杯') + 3);
	//printf("blakgjsdf %lu\n", ft_wchar_len(L''));
	return (0);
}
