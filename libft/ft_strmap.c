/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 20:45:13 by yabdulha          #+#    #+#             */
/*   Updated: 2018/03/17 23:01:40 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap_p(char *s, char (*f)(char))
{
	int		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	while (s[i] != '\0')
	{
		s[i] = f(s[i]);
		i++;
	}
	return (s);
}

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new;
	int		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	if (!(new = (char*)malloc(sizeof(*new) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[i] != '\0')
	{
		new[i] = f(s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
