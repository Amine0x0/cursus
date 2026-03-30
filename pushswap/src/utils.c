/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:27:09 by amine             #+#    #+#             */
/*   Updated: 2025/03/23 18:28:23 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	cleanup(t_node **stack_a, t_node **stack_b)
{
	t_node	*temp;

	while (*stack_a)
	{
		temp = *stack_a;
		*stack_a = (*stack_a)->next;
		free(temp);
	}
	while (*stack_b)
	{
		temp = *stack_b;
		*stack_b = (*stack_b)->next;
		free(temp);
	}
}

int	is_sorted(t_node *stack)
{
	t_node	*current;

	current = stack;
	while (current && current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

void	stack_clear(t_node **head)
{
	t_node	*cur;
	t_node	*nxt;

	cur = *head;
	while (cur)
	{
		nxt = cur->next;
		free(cur);
		cur = nxt;
	}
	*head = NULL;
}

int	push_back(t_node **head, int n)
{
	t_node	*new;
	t_node	*tmp;

	new = new_stack(n);
	if (!new)
		return (0);
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

t_node	*new_stack(int n)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->value = n;
	new->index = -1;
	new->next = NULL;
	return (new);
}
