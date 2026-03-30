/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:35:55 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/05 15:35:57 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	stack_pos(t_node *stack, t_node *node)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack == node)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}

t_node	*find_max(t_node *stack_b)
{
	t_node	*max_node;

	max_node = stack_b;
	while (stack_b)
	{
		if (stack_b->value > max_node->value)
			max_node = stack_b;
		stack_b = stack_b->next;
	}
	return (max_node);
}

void	sort_stack(t_node **stack_a, t_node **stack_b)
{
	int		median;
	t_node	*max_node;

	push_to_b(stack_a, stack_b);
	add_index(*stack_b);
	if (!(*stack_b))
		return ;
	while (*stack_b)
	{
		median = get_stack_size(*stack_b) / 2;
		max_node = find_max(*stack_b);
		if (stack_pos(*stack_b, max_node) <= median)
		{
			while (*stack_b && *stack_b != max_node)
				rb(stack_b);
		}
		else
		{
			while (*stack_b && *stack_b != max_node)
				rrb(stack_b);
		}
		pa(stack_a, stack_b);
	}
	stack_clear(stack_b);
}
