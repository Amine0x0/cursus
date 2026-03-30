/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:11:37 by amine             #+#    #+#             */
/*   Updated: 2025/03/23 18:11:39 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	add_front(t_node **head, t_node *new)
{
	if (!head || !new)
		return ;
	new->next = *head;
	*head = new;
}

void	push(t_node **dst, t_node **src)
{
	t_node	*tmp;

	tmp = *src;
	*src = (*src)->next;
	tmp->next = NULL;
	add_front(dst, tmp);
}

void	pb(t_node **stack_a, t_node **stack_b)
{
	if (!get_stack_size(*stack_a))
		return ;
	push(stack_b, stack_a);
	write(1, "pb\n", 3);
}

void	pa(t_node **stack_a, t_node **stack_b)
{
	if (!get_stack_size(*stack_b))
		return ;
	push(stack_a, stack_b);
	write(1, "pa\n", 3);
}
