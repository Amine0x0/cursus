/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:41:51 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/05 15:41:52 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	index_stack(t_node *stack)
{
	t_node	*node;
	int		index;
	t_node	*smallest;

	index = 0;
	while (index < get_stack_size(stack))
	{
		node = stack;
		smallest = NULL;
		while (node)
		{
			if (node->index == -1 && (!smallest
					|| node->value < smallest->value))
				smallest = node;
			node = node->next;
		}
		if (smallest)
			smallest->index = index++;
	}
}

void	add_index(t_node *stack)
{
	t_node	*current;
	int		index;

	current = stack;
	index = 0;
	while (current)
	{
		current->index = index;
		index++;
		current = current->next;
	}
}
