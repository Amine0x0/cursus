/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:39:39 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/04 10:49:40 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	is_digit_str(const char *s)
{
	if (!s || !*s)
		return (0);
	if (*s == '+' || *s == '-')
		s++;
	if (!*s)
		return (0);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

static void	print_exit_error(const char *msg, int code)
{
	print_err("exit: %s\n", msg);
	exit(code);
}

static unsigned long long	parse_number(const char *arg)
{
	int						i;
	unsigned long long		value;
	const char				*num_str;
	unsigned int			digit;

	if (arg[0] == '+' || arg[0] == '-')
		num_str = arg + 1;
	else
		num_str = arg;
	value = 0;
	i = 0;
	while (num_str[i])
	{
		digit = num_str[i] - '0';
		if (value > (ULLONG_MAX - digit) / 10)
			print_exit_error("numeric argument required", 255);
		value = value * 10 + digit;
		i++;
	}
	return (value);
}

static void	validate_range(unsigned long long value, int negative)
{
	if (negative)
	{
		if (value > (unsigned long long)LLONG_MAX + 1ULL)
			print_exit_error("numeric argument required", 255);
	}
	else
	{
		if (value > (unsigned long long)LLONG_MAX)
			print_exit_error("numeric argument required", 255);
	}
}

int	builtin_exit(char **args)
{
	unsigned long long	value;
	int					negative;
	long long			val;

	if (!args[1])
		(close_extra_fds(), exit(0));
	if (args[2])
	{
		print_err("exit: too many arguments\n", NULL);
		return (1);
	}
	if (!is_digit_str(args[1]))
		(close_extra_fds(), print_exit_error("numeric argument required", 255));
	negative = (args[1][0] == '-');
	value = parse_number(args[1]);
	validate_range(value, negative);
	if (negative)
		val = -(long long)value;
	else
		val = (long long)value;
	close_extra_fds();
	exit((int)(val & 0xFF));
}
