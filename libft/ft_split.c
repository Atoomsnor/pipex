/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:05:20 by roversch          #+#    #+#             */
/*   Updated: 2024/10/29 18:23:11 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_count(char const *s, char c)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			nb++;
		i++;
	}
	return (nb);
}

static int	ft_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_free(char **split_str)
{
	int	i;

	i = 0;
	if (split_str)
	{
		while (split_str[i])
		{
			free(split_str[i]);
			i++;
		}
		free(split_str);
	}
	return (NULL);
}

static char	**ft_bigsplit(char const *s, char c, char **n_str)
{
	int	i;
	int	j;
	int	w_len;

	i = 0;
	j = 0;
	w_len = 0;
	if (!n_str)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			w_len = ft_len(s + i, c);
			n_str[j] = ft_substr(s, i, w_len);
			if (!n_str[j])
				return (ft_free(n_str));
			i += w_len;
			j++;
		}
	}
	n_str[j] = NULL;
	return (n_str);
}

char	**ft_split(char const *s, char c)
{
	char	**n_str;

	if (!s)
		return (NULL);
	n_str = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!n_str)
		return (NULL);
	return (ft_bigsplit(s, c, n_str));
}
