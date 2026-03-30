/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:12:07 by amine             #+#    #+#             */
/*   Updated: 2025/03/23 18:12:08 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rotate(t_node **stack)
{
	t_node	*tmp;
	t_node	*second;
	t_node	*last;

	if (*stack == NULL || (*stack)->next == NULL)
		return ;
	last = *stack;
	tmp = *stack;
	second = (*stack)->next;
	while (last->next)
		last = last->next;
	last->next = tmp;
	*stack = second;
	tmp->next = NULL;
}

void	ra(t_node **stack_a)
{
	if (get_stack_size(*stack_a) <= 1)
		return ;
	rotate(stack_a);
	write(1, "ra\n", 3);
}

void	rb(t_node **stack_b)
{
	if (get_stack_size(*stack_b) <= 1)
		return ;
	rotate(stack_b);
	write(1, "rb\n", 3);
}

void	rr(t_node **stack_a, t_node **stack_b)
{
	if (get_stack_size(*stack_a) <= 1 || get_stack_size(*stack_b) <= 1)
		return ;
	rotate(stack_a);
	rotate(stack_b);
	write(1, "rr\n", 3);
}
