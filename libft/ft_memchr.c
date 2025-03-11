/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:07:08 by roversch          #+#    #+#             */
/*   Updated: 2024/10/18 15:07:30 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		chr;

	str = (const unsigned char *)s;
	chr = (unsigned char)c;
	while (n-- > 0)
	{
		if (*str == chr)
			return ((void *)str);
		str++;
	}
	return (NULL);
}
