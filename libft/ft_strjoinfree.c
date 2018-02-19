/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:32:17 by yabdulha          #+#    #+#             */
/*   Updated: 2018/02/04 16:06:55 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char const *s2)
{
	char	*new;
	int		i;
	int		len1;
	int		len;

	if (!(s1 && s2))
		return (NULL);
	len1 = ft_strlen(s1);
	len = len1 + ft_strlen(s2);
	if (!(new = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (i < len1)
			new[i] = s1[i];
		if (i < (len - len1))
			new[i + len1] = s2[i];
		i++;
	}
	free(s1);
	return (new);
}
