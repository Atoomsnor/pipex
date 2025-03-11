/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:40:30 by roversch          #+#    #+#             */
/*   Updated: 2025/02/18 12:59:27 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

int	ft_format(const char format, va_list args)
{
	int	printlen;

	printlen = 0;
	if (format == 'c')
		printlen += ft_print_char(va_arg(args, int));
	else if (format == 's')
		printlen += ft_print_str(va_arg(args, char *));
	else if (format == 'p')
		printlen += ft_print_ptr(va_arg(args, unsigned long));
	else if (format == 'd' || format == 'i')
		printlen += ft_print_nbr(va_arg(args, int));
	else if (format == 'u')
		printlen += ft_print_uns_deci(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		printlen += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		printlen += ft_print_char('%');
	return (printlen);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		printlen;
	va_list	args;

	i = 0;
	printlen = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			printlen += ft_format(str[i + 1], args);
			i++;
		}
		else
			printlen += ft_print_char(str[i]);
		i++;
	}
	va_end(args);
	return (printlen);
}
