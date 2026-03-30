/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:33:03 by amabbadi          #+#    #+#             */
/*   Updated: 2025/07/26 22:26:05 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	is_arg_valid(char *arg)
{
	if (!arg || !*arg)
		return (false);
	while (*arg && ((*arg >= 9 && *arg <= 13) || *arg == ' '))
		arg++;
	if (!*arg)
		return (false);
	while (*arg)
	{
		if (!ft_isdigit((unsigned char)*arg))
			return (false);
		arg++;
	}
	return (true);
}

bool	fill_metadata(int argc, char **argv, t_meta *meta)
{
	int	i;
	int	j;

	meta->argc = argc;
	meta->argv = malloc(sizeof(char *) * argc);
	if (!meta->argv)
		return (false);
	i = 0;
	while (i < argc)
	{
		meta->argv[i] = ft_strdup(argv[i]);
		if (!meta->argv[i])
		{
			j = 0;
			while (j < i)
			{
				free(meta->argv[j]);
				j++;
			}
			free(meta->argv);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	check_arg_count(int argc)
{
	const char	*argument_errors[] = {"number of philosophers is missing",
		"time to die is missing", "time to eat is missing",
		"time to sleep is missing"};

	if (argc > 5)
		return (printf("too many arguments.\n"), false);
	if (argc < 4)
		return (printf("%s\n", argument_errors[argc]), false);
	return (true);
}

bool	validate_arg_value(int index, char *arg)
{
	long	val;

	if (!is_arg_valid(arg))
	{
		printf("argument not valid at index [%d]\n", index);
		return (false);
	}
	val = ft_atol(arg);
	if (val == FT_ATOL_ERROR)
	{
		printf("syntax error: argument at index \
[%d] causes overflow/underflow\n",
			index);
		return (false);
	}
	if (val <= 0 || val >= INT_MAX)
	{
		if (index == 0)
			printf("syntax error: num of philos.\n");
		else
			printf("syntax error: argument at index [%d] is out of range\n",
				index);
		return (false);
	}
	return (true);
}

bool	parse_check(int argc, char **argv, t_meta *meta)
{
	int	i;

	if (!check_arg_count(argc))
		return (false);
	i = 0;
	while (i < argc)
	{
		if (!validate_arg_value(i, argv[i]))
			return (false);
		i++;
	}
	return (fill_metadata(argc, argv, meta));
}
