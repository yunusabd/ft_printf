/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 16:29:14 by yabdulha          #+#    #+#             */
/*   Updated: 2018/04/25 16:44:48 by yabdulha         ###   ########.fr       */
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
	while (*(++fstr))
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
	}
	return (fstr);
}

static char	*find_specifier(char *str, t_printf *specs)
{
	while (*(++str))
	{
		if ((ft_strchr(SPECIFIERS, *str)))
			return (str);
		if (ft_isalpha(*str) && !(ft_strchr(VALID_CHARS, *str)))
		{
			specs->converter = '0';
			return (str);
		}
	}
	return (NULL);
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

char		*parse_spec(char *str, t_printf *specs)
{
	char		*pos;
	char		*fstr;
	char		*tmp;

	pos = NULL;
	if ((pos = find_specifier(str, specs)))
	{
		if (ft_strchr(SPECIFIERS, *pos))
			specs->converter = *pos;
		else
			specs->converter = '0';
		fstr = ft_strndup(str, pos + 1 - str);
		tmp = fstr;
		fstr = get_flags(fstr, specs);
		if (!(get_width(specs, pos)))
			specs->width = -1;
		if (!(get_precision(specs, pos)))
			specs->precision = -1;
		fstr = get_len(fstr, specs);
		free(tmp);
		//print_struct(specs);
		if (specs->converter == '0')
			return (pos);
		return (pos + 1);
	}
	return (str + 1);
}
