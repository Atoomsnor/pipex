/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:06:54 by roversch          #+#    #+#             */
/*   Updated: 2024/10/28 14:27:33 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	l_len;
	size_t	i;
	size_t	j;

	l_len = 0;
	i = 0;
	while (little[l_len])
		l_len++;
	if (l_len == 0)
		return ((char *)big);
	while (big[i] && i <= len - l_len)
	{
		j = 0;
		if (j + i >= len || l_len > len)
			return (NULL);
		while (j < l_len && big[i + j] == little[j])
			j++;
		if (j == l_len)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
