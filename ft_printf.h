/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 12:03:52 by yabdulha          #+#    #+#             */
/*   Updated: 2018/02/19 15:18:43 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

#include <stdarg.h>
#include <stdio.h>
#include "libft/libft.h"
#include <locale.h>

#define SPECIFIERS "sSpdDioOuUxXcCb"
#define SP_LEN (ft_strlen(SPECIFIERS))

typedef struct s_printf
{
	int			iszero;
	int			isspace;
	int			ishash;
	int			isminus;
	int			isplus;

	int			width;
	int			precision;

	int			ishh;
	int			ish;
	int			isll;
	int			isl;
	int			isj;
	int			isz;
	char		converter;

}				t_printf;

#endif
