/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:16:27 by roversch          #+#    #+#             */
/*   Updated: 2024/10/18 14:20:10 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_i;
	const unsigned char	*src_i;
	size_t				i;

	if (dest == 0 && src == 0)
		return (NULL);
	dest_i = (unsigned char *)dest;
	src_i = (const unsigned char *)src;
	i = 0;
	while (n > i)
	{
		dest_i[i] = src_i[i];
		i++;
	}
	return (dest_i);
}
