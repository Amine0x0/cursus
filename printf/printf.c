/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:09:40 by amabbadi          #+#    #+#             */
/*   Updated: 2025/01/27 08:56:09 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_specifier(char specifier, va_list args)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (specifier == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (specifier == 'u')
		count += ft_putuint(va_arg(args, unsigned int));
	else if (specifier == 'x')
		count += ft_putx(va_arg(args, unsigned int));
	else if (specifier == 'X')
		count += ft_putxa(va_arg(args, unsigned int));
	else if (specifier == '%')
		count += ft_putchar('%');
	else if (specifier == 'p')
		count += ft_putptr(va_arg(args, void *));
	else
		count += ft_putchar(specifier);
	return (count);
}

int	ft_printf(const char *input, ...)
{
	va_list		args;
	int			count;
	const char	*ptr;

	if (!input)
		return (-1);
	count = 0;
	va_start(args, input);
	ptr = input;
	if (write(1, "", 0) < 0)
		return (va_end(args), -1);
	while (*ptr)
	{
		if (*ptr == '%')
		{
			ptr++;
			if (!*ptr)
				return (va_end(args), -1);
			count += handle_specifier(*ptr, args);
		}
		else
			count += ft_putchar(*ptr);
		ptr++;
	}
	return (va_end(args), count);
}
