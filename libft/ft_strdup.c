/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:06:20 by roversch          #+#    #+#             */
/*   Updated: 2024/10/28 13:48:31 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*dup_str;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	dup_str = malloc(len + 1);
	if (dup_str == NULL)
		return (NULL);
	while (i < len)
	{
		dup_str[i] = s[i];
		i++;
	}
	dup_str[len] = '\0';
	return (dup_str);
}
