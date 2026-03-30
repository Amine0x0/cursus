/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:15:38 by amine             #+#    #+#             */
/*   Updated: 2025/03/23 18:16:03 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	swap(t_node **stack)
{
	t_node	*first;
	t_node	*second;

	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
}

void	sa(t_node **stack_a)
{
	if (get_stack_size(*stack_a) <= 1)
		return ;
	swap(stack_a);
	write(1, "sa\n", 3);
}

void	sb(t_node **stack_b)
{
	if (get_stack_size(*stack_b) <= 1)
		return ;
	swap(stack_b);
	write(1, "sb\n", 3);
}

void	ss(t_node **stack_a, t_node **stack_b)
{
	if (get_stack_size(*stack_a) <= 1 || get_stack_size(*stack_b) <= 1)
		return ;
	swap(stack_a);
	swap(stack_b);
	write(1, "ss\n", 3);
}
