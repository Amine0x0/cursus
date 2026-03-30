/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_hexautils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:10:38 by amabbadi          #+#    #+#             */
/*   Updated: 2025/01/25 00:37:34 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	len;

	if (str == NULL)
		return (ft_putstr("(null)"));
	len = 0;
	while (str[len])
	{
		ft_putchar(str[len]);
		len++;
	}
	return (len);
}

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return (11);
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
		count++;
	}
	if (n >= 10)
		count += ft_putnbr(n / 10);
	count += ft_putchar((n % 10) + '0');
	return (count);
}

int	ft_putuint(unsigned int num)
{
	int	count;

	count = 0;
	if (num >= 10)
		count += ft_putuint(num / 10);
	count += ft_putchar((num % 10) + '0');
	return (count);
}
