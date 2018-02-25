/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 20:44:26 by yabdulha          #+#    #+#             */
/*   Updated: 2018/02/24 21:49:28 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*find_specifier(const char *str, t_printf *specs)
{
	char	*ptr;

	ptr = NULL;
	while (str++)
	{
		if (ft_isalpha(*str) && !(ft_strchr(SPECIFIERS, *str)))
		{
			specs->converter = 0;
			return (ptr);
		}
		if ((ptr = ft_strpbrk(str, SPECIFIERS)))
			return (ptr);
	}
	return (ptr);
}

static char	*get_flags(char *fstr, t_printf *new)
{
	new->ishash = 0;
	new->iszero = 0;
	new->isminus = 0;
	new->isspace = 0;
	new->isplus = 0;
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

/*
static char	*get_width(char *fstr, t_printf *specs, char *spec_pos)
{
	specs->width = ft_atoi(fstr);
	while (*fstr && ft_isdigit(*fstr))
		fstr++;
	return (fstr);
}
*/

static int	get_width(t_printf *specs, char *spec_pos)
{
	char	*pos;

	pos = spec_pos;
	while (*pos != '%')
	{
		if (ft_isdigit(*pos) && (!(ft_isdigit(*(pos - 1)))) && *(pos - 1) != '.')
		{
			specs->width = ft_atoi(pos);
			return (1);
		}
		pos--;
	}
	return (0);
}

static int	get_precision(t_printf *specs, char *spec_pos)
{
	char	*pos;

	pos = spec_pos;
	specs->precision = -1;
	while (*pos != '%')
	{
		if (*pos == '.')
		{
			specs->precision = ft_atoi(pos + 1);
			return (1);
		}
		pos--;
	}
	return (0);
}

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

/*
** TODO If no converter is found, print the characters
*/

static char	*get_converter(char *fstr, t_printf *specs)
{
	char	*res;

	res = ft_strchr(SPECIFIERS, *fstr);
	if (res == NULL)
	{
		printf("fail\n");
		exit(0);
	}
	specs->converter = *res;
	return (fstr++);
}

char		*parse_spec(const char *str, t_printf *specs)
{
	char		*pos;
	char		*fstr;

	pos = NULL;
	if ((pos = find_specifier(str, specs)))
	{
		ft_strncpy(&specs->converter, pos, 1);
		fstr = ft_strdup_until(str, pos + 1);
		fstr = get_flags(fstr, specs);
		if (!(get_width(specs, pos)))
			specs->width = -1;
		if (!(get_precision(specs, pos)))
			specs->precision = -1;
		fstr = get_len(fstr, specs);
		//fstr = find_specifier(fstr, specs);
		/*printf("flags: ishash [%d]\n", specs->ishash);
		printf("flags: converter [%c]\n", specs->converter);
		printf("flags: width [%d]\n", specs->width);
		printf("flags: precision [%d]\n", specs->precision);
		printf("flags: isll [%d]\n__________________\n", specs->isll);
		printf("fstr %s\n", pos);
		*/
		return (pos + 1);
	}
	return (pos);
}
