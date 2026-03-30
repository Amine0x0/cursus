/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:08:23 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/05 17:08:25 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
/*random goofy funcs v2*/
int	ft_isblank(char c)
{
	if (c <= 32)
		return (1);
	return (0);
}

int	ft_isvalid(char c, int base)
{
	int		i;
	char	digit;
	char	digit2;

	i = 0;
	while (i < base)
	{
		digit = BASE_16_CHARSET[i];
		digit2 = BASE_16_CHARSET[i] + 32;
		if (c == digit || c == digit2)
			return (1);
		i++;
	}
	return (0);
}

int	ft_value_of(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	result;
	int	sign;

	result = 0;
	while (ft_isblank(*str))
		str++;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isvalid(*str, str_base))
	{
		result = result * str_base + ft_value_of(*str);
		str++;
	}
	return (result * sign);
}
