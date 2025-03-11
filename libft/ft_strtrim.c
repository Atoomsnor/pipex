/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:57:02 by roversch          #+#    #+#             */
/*   Updated: 2024/10/21 17:40:28 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	int		substr_len;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i])
	{
		if (!ft_strchr (set, s1[i]))
			break ;
		i++;
	}
	while (j > i)
	{
		if (!ft_strchr (set, s1[j]))
			break ;
		j--;
	}
	substr_len = (j - i + 1);
	return (ft_substr (s1, i, substr_len));
}
