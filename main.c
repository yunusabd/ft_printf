/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 23:06:43 by yabdulha          #+#    #+#             */
/*   Updated: 2018/03/08 22:27:47 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_printf(const char *format, ...);

#include <wchar.h>

int		main()
{
	char		*str = "中文";
	char		*this = "this is a string";
	int			myiny = 42;
	char		c = 'a';
	char		*ptr;
	wchar_t		*wc = L"蹩鎞";
	const wchar_t me = 0x1F378;
	int			res;

	//printf("%.s", "popo");
	res = ft_printf("[%s]", this);
	printf("\ntest: [%.8s]\n", this);
	//printf("\nprintf string:\n[%ls]", wc);
	//write(1, "[杯]\n", ft_wchar_len(L'杯') + 3);
	//printf("blakgjsdf %lu\n", ft_wchar_len(L''));
	return (0);
}
