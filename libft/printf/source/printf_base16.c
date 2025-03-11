/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_base16.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:32:21 by roversch          #+#    #+#             */
/*   Updated: 2025/02/18 12:59:35 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_print_hex(unsigned int n, const char format)
{
	int	i;

	i = 0;
	if (n >= 16)
	{
		i += ft_print_hex(n / 16, format);
		i += ft_print_hex(n % 16, format);
	}
	else
	{
		if (n <= 9)
			i += ft_print_char(n + '0');
		else
		{
			if (format == 'x')
				i += ft_print_char(n - 10 + 'a');
			if (format == 'X')
				i += ft_print_char(n - 10 + 'A');
		}
	}
	return (i);
}

int	ft_put_ptr(unsigned long n)
{
	int	i;

	i = 0;
	if (n >= 16)
	{
		i += ft_put_ptr(n / 16);
		i += ft_put_ptr(n % 16);
	}
	else
	{
		if (n <= 9)
			i += ft_print_char(n + '0');
		else
			i += ft_print_char(n - 10 + 'a');
	}
	return (i);
}

int	ft_print_ptr(unsigned long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	i += ft_put_ptr(n);
	return (i + 2);
}
