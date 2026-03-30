/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reroll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:41:37 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/05 15:41:38 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_range(t_node **stack_a)
{
	int	size;

	size = get_stack_size(*stack_a);
	if (size > 100)
		return (32);
	else
		return (11);
}

int	protect(t_node **stack_a)
{
	int		i;
	int		j;
	t_node	*head;

	i = 0;
	j = 0;
	head = *stack_a;
	while (j < get_stack_size(*stack_a) / 2)
	{
		if (head->value > head->next->value)
			i++;
		j++;
		head = head->next;
	}
	return (i);
}

void	init_push_b(t_node **stack_a, int *index, int *range, int *is_chaotic)
{
	*index = 0;
	*is_chaotic = protect(stack_a) > (get_stack_size(*stack_a)) / 3;
	*range = ft_range(stack_a);
}

void	push_to_b(t_node **stack_a, t_node **stack_b)
{
	int		index;
	int		range;
	t_node	*head;
	int		is_chaotic;

	init_push_b(stack_a, &index, &range, &is_chaotic);
	while (*stack_a)
	{
		head = *stack_a;
		if (head->index <= index)
		{
			pb(stack_a, stack_b);
			index++;
		}
		else if (head->index <= (index + range))
		{
			pb(stack_a, stack_b);
			rb(stack_b);
			index++;
		}
		else if (is_chaotic)
			rra(stack_a);
		else
			ra(stack_a);
	}
}
