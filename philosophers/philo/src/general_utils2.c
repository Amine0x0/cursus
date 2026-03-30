/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 02:31:41 by amabbadi          #+#    #+#             */
/*   Updated: 2025/07/26 04:21:05 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	ft_atol_init(int *i, int *sign, long *limit, int *last_digit_limit)
{
	*i = 0;
	*sign = 1;
	*limit = LONG_MAX / 10;
	*last_digit_limit = 7;
}

static bool	ft_atol_check_overflow(long res, long limit, int digit,
		int last_digit_limit)
{
	if (res > limit)
		return (true);
	if (res == limit && digit > last_digit_limit)
		return (true);
	return (false);
}

long	ft_atol(const char *str)
{
	int			i;
	long		res;
	int			sign;
	long		limit;
	int			last_digit_limit;

	res = 0;
	ft_atol_init(&i, &sign, &limit, &last_digit_limit);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
		{
			sign = -1;
			last_digit_limit = 8;
		}
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ft_atol_check_overflow(res, limit, str[i] - '0', last_digit_limit))
			return (FT_ATOL_ERROR);
		res = res * 10 + (str[i++] - '0');
	}
	return (res * sign);
}
