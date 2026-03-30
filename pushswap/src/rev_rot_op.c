/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rot_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:42:12 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/05 15:42:13 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	reverse_rotate(t_node **stack)
{
	t_node	*tmp;
	t_node	*last;
	t_node	*second_to_last;

	tmp = *stack;
	last = *stack;
	second_to_last = *stack;
	while (last->next)
	{
		second_to_last = last;
		last = last->next;
	}
	second_to_last->next = NULL;
	last->next = tmp;
	*stack = last;
}

void	rra(t_node **stack_a)
{
	if (get_stack_size(*stack_a) <= 1)
		return ;
	reverse_rotate(stack_a);
	write(1, "rra\n", 4);
}

void	rrb(t_node **stack_b)
{
	if (get_stack_size(*stack_b) <= 1)
		return ;
	reverse_rotate(stack_b);
	write(1, "rrb\n", 4);
}

void	rrr(t_node **stack_a, t_node **stack_b)
{
	if (get_stack_size(*stack_a) <= 1 || get_stack_size(*stack_b) <= 1)
		return ;
	reverse_rotate(stack_a);
	reverse_rotate(stack_b);
	write(1, "rrr\n", 4);
}
