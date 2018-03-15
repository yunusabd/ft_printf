/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 16:29:14 by yabdulha          #+#    #+#             */
/*   Updated: 2018/03/15 18:54:02 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static char	*set_len(char *fstr, int *len_conv, int offset)
{
	*len_conv = 1;
	return (fstr += offset);
}

static char	*get_len(char *fstr, t_printf *specs)
{
	specs->ishh = 0;
	specs->ish = 0;
	specs->isll = 0;
	specs->isl = 0;
	specs->isj = 0;
	specs->isz = 0;
	if (!fstr || !ft_isalpha(*fstr))
		return (fstr);
	if (ft_strncmp(fstr, "ll", 2) == 0)
		return (set_len(fstr, &specs->isll, 2));
	else if (ft_strncmp(fstr, "hh", 2) == 0)
		return (set_len(fstr, &specs->ishh, 2));
	else if (ft_strncmp(fstr, "l", 1) == 0)
		return (set_len(fstr, &specs->isl, 1));
	else if (ft_strncmp(fstr, "h", 1) == 0)
		return (set_len(fstr, &specs->ish, 1));
	else if (ft_strncmp(fstr, "j", 1) == 0)
		return (set_len(fstr, &specs->isj, 1));
	else if (ft_strncmp(fstr, "z", 1) == 0)
		return (set_len(fstr, &specs->isz, 1));
	else
		return (fstr);
}

static char	*get_flags(char *fstr, t_printf *new)
{
	new->ishash = 0;
	new->iszero = 0;
	new->isminus = 0;
	new->isspace = 0;
	new->isplus = 0;
	while (fstr)
	{
		if (*fstr == '#')
			new->ishash = 1;
		else if (*fstr == '0')
			new->iszero = 1;
		else if (*fstr == '-')
			new->isminus = 1;
		else if (*fstr == ' ')
			new->isspace = 1;
		else if (*fstr == '+')
			new->isplus = 1;
		else
			return (fstr);
		fstr++;
	}
	return (fstr);
}

static char	*find_specifier(const char *str, t_printf *specs)
{
	char	*ptr;

	ptr = NULL;
	while (*str)
	{
		if ((ptr = ft_strpbrk(str, SPECIFIERS)))
			return (ptr);
		if (ft_isalpha(*str) && !(ft_strchr(SPECIFIERS, *str)))
			specs->converter = 0;
		str++;
	}
	return (ptr);
}

static int	get_width(t_printf *specs, char *spec_pos)
{
	char	*pos;

	pos = spec_pos;
	while (*(--pos) != '%')
	{
		if (ft_isdigit(*pos) && (!(ft_isdigit(*(pos - 1))))
				&& *(pos - 1) != '.')
		{
			specs->width = ft_atoi(pos);
			return (1);
		}
	}
	return (0);
}

static int	get_precision(t_printf *specs, char *spec_pos)
{
	char	*pos;

	pos = spec_pos;
	specs->precision = -1;
	while (*(--pos) != '%')
	{
		if (*pos == '.')
		{
			specs->precision = ft_atoi(pos + 1);
			return (1);
		}
	}
	return (0);
}

/*
** TODO If no converter is found, print the characters
*/

static char	*handle_percent(const char *str, char *pos, t_printf *specs)
{
	char	*fstr;

	printf("fstr: %s\n", str);
	specs->converter = '%';
	fstr = ft_strdup_until(str, pos + 1);

	fstr = get_flags(fstr, specs);
	if (!(get_width(specs, pos)))
		specs->width = -1;
	if (!(get_precision(specs, pos)))
		specs->precision = -1;
	fstr = get_len(fstr, specs);
	return (pos);
}

char		*parse_spec(const char *str, t_printf *specs)
{
	char		*pos;
	char		*fstr;

	pos = NULL;
	specs->negative = 0;
	specs->printed = 0;
	if ((pos = find_specifier(str, specs)))
	{
		if (*pos == '%')
			return (handle_percent(str, pos, specs));
		ft_strncpy(&specs->converter, pos, 1);
		fstr = ft_strdup_until(str, pos + 1);
		fstr = get_flags(fstr, specs);
		if (!(get_width(specs, pos)))
			specs->width = -1;
		if (!(get_precision(specs, pos)))
			specs->precision = -1;
		fstr = get_len(fstr, specs);
		return (pos + 1);
	}
	return (pos);
}
