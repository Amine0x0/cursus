/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:24:46 by amabbadi          #+#    #+#             */
/*   Updated: 2025/01/27 08:56:23 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void *ptr)
{
	unsigned long	address;
	char			*hex_chars;
	char			buffer[16];
	int				count;
	int				i;

	hex_chars = "0123456789abcdef";
	count = 0;
	i = 0;
	if (!ptr)
		return (ft_putstr("0x0"));
	address = (unsigned long)ptr;
	count += ft_putstr("0x");
	if (address == 0)
		return (count += ft_putchar('0'), count);
	while (address > 0)
	{
		buffer[i++] = hex_chars[address % 16];
		address /= 16;
	}
	while (i > 0)
		count += ft_putchar(buffer[--i]);
	return (count);
}

int	ft_putx(unsigned int num)
{
	char	*hex_chars;
	char	buffer[8];
	int		count;
	int		i;

	hex_chars = "0123456789abcdef";
	count = 0;
	i = 0;
	if (num == 0)
	{
		ft_putchar('0');
		return (1);
	}
	while (num > 0)
	{
		buffer[i++] = hex_chars[num % 16];
		num /= 16;
	}
	while (i > 0)
		count += ft_putchar(buffer[--i]);
	return (count);
}

int	ft_putxa(unsigned int num)
{
	char	*hex_chars;
	char	buffer[8];
	int		count;
	int		i;

	hex_chars = "0123456789ABCDEF";
	count = 0;
	i = 0;
	if (num == 0)
	{
		ft_putchar('0');
		return (1);
	}
	while (num > 0)
	{
		buffer[i++] = hex_chars[num % 16];
		num /= 16;
	}
	while (i > 0)
		count += ft_putchar(buffer[--i]);
	return (count);
}
