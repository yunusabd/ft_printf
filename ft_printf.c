/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 20:44:26 by yabdulha          #+#    #+#             */
/*   Updated: 2018/02/19 15:49:55 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*find_specifier(const char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	while (i < SP_LEN)
	{
		if ((ptr = ft_strchr(str, SPECIFIERS[i])))
			return (ptr);
		i++;
	}
	return (NULL);
}

char	*get_flags(char *fstr, t_printf *new)
{
	while (*(++fstr))
	{
		if (*fstr == '#')
		{
			printf("ushasj\n");
			new->ishash = 1;
		}
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

char	*get_width(char *fstr, t_printf *specs)
{
	specs->width = ft_atoi(fstr);
	while (*fstr && ft_isdigit(*fstr))
		fstr++;
	return (fstr);
}

char	*get_precision(char *fstr, t_printf *specs)
{
	if (*fstr && *fstr == '.')
		fstr++;
	else
		return (fstr);
	if (!(ft_isdigit(*fstr)))
		return (fstr);
	specs->precision = ft_atoi(fstr);
	while (*fstr && ft_isdigit(*fstr))
		fstr++;
	return (fstr);
}

char	*set_len(char *fstr, int *len_conv, int offset)
{
	*len_conv = 1;
	return (fstr += offset);
}

char	*get_len(char *fstr, t_printf *specs)
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

char	*get_converter(char *fstr, t_printf *specs)
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

char	*parse_spec(const char *str, t_printf *specs)
{
	char		*pos;
	char		*fstr;
	
	if ((pos = find_specifier(str)))
	{
		fstr = ft_strdup_until(str, pos + 1);
		fstr = get_flags(fstr, specs);
		fstr = get_width(fstr, specs);
		fstr = get_precision(fstr, specs);
		fstr = get_len(fstr, specs);
		fstr = get_converter(fstr, specs);
		printf("flags: ishash [%d]\n", specs->ishash);
		printf("flags: converter [%c]\n", specs->converter);
		printf("flags: isll [%d]\n__________________\n", specs->isll);
		return (((pos) == '\0') ? 0 : (pos));
	}
	return (0);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	int			len;
	t_printf	new;

	va_start(ap, format);
	len = ft_strlen(format);
	i = 0;
	while (i < len && format)
	{
		if (format[i] != '%')
		{
			//printf(" [%c] ", format[i]);
			//ft_putchar(format[i]);
			i++;
		}
		else 
		{
			format = parse_spec(format + i, &new);
			i = 0;
		}
	}
	va_end(ap);
	return (1);
}

int		main()
{
	char		*input = "ft_printf - input string: %s, intput int: %#01.12lld\n";
	char		*str = "mystring";
	int			myiny = 42;
	char		c = 'a';
	char		*ptr;

	ft_printf(input);
	//printf(input, str, myiny);
	return (0);
}
