/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:17:02 by amine             #+#    #+#             */
/*   Updated: 2025/03/23 18:25:22 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	main(int ac, char **av)
{
	t_node	*stack_a;
	t_node	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (ac >= 2)
	{
		parse_input(ac, av, &stack_a);
		index_stack(stack_a);
		if (is_sorted(stack_a))
			return (stack_clear(&stack_a), 0);
		if (get_stack_size(stack_a) == 2)
			sa(&stack_a);
		else if (get_stack_size(stack_a) == 3)
			sorting_3(&stack_a);
		else if (get_stack_size(stack_a) == 4)
			sorting_4(&stack_a, &stack_b);
		else if (get_stack_size(stack_a) == 5)
			sorting_5(&stack_a, &stack_b);
		else
			sort_stack(&stack_a, &stack_b);
	}
	stack_clear(&stack_a);
}
