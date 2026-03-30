/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_fast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:42:25 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/05 15:42:26 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	find_min_index(t_node *stack)
{
	int	min;
	int	index;
	int	min_index;

	min = stack->value;
	index = 0;
	min_index = 0;
	while (stack)
	{
		if (stack->value < min)
		{
			min = stack->value;
			min_index = index;
		}
		stack = stack->next;
		index++;
	}
	return (min_index);
}

int	sorting_5(t_node **stack_a, t_node **stack_b)
{
	int	min_index;

	min_index = find_min_index(*stack_a);
	if (min_index == 1)
		sa(stack_a);
	else if (min_index == 2)
	{
		ra(stack_a);
		ra(stack_a);
	}
	else if (min_index == 3)
	{
		rra(stack_a);
		rra(stack_a);
	}
	else if (min_index == 4)
		rra(stack_a);
	pb(stack_a, stack_b);
	sorting_4(stack_a, stack_b);
	pa(stack_a, stack_b);
	return (0);
}

int	sorting_4(t_node **stack_a, t_node **stack_b)
{
	int	min_index;

	min_index = find_min_index(*stack_a);
	if (min_index == 1)
		sa(stack_a);
	else if (min_index == 2)
	{
		ra(stack_a);
		ra(stack_a);
	}
	else if (min_index == 3)
		rra(stack_a);
	pb(stack_a, stack_b);
	sorting_3(stack_a);
	pa(stack_a, stack_b);
	return (0);
}

int	sorting_3(t_node **stack_a)
{
	t_node	*first;
	t_node	*second;
	t_node	*third;

	if (!stack_a || !(*stack_a) || !(*stack_a)->next || !(*stack_a)->next->next)
		return (0);
	while (!is_sorted(*stack_a))
	{
		first = *stack_a;
		second = first->next;
		third = second->next;
		if (second->value > first->value && second->value > third->value)
			rra(stack_a);
		else if (first->value > second->value && first->value > third->value)
			ra(stack_a);
		first = *stack_a;
		second = first->next;
		if (first->value > second->value)
			sa(stack_a);
	}
	return (0);
}
