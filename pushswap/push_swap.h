/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:46:33 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/10 01:28:53 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
}					t_node;

long long	ft_atoi(const char *str);
void		cleanup(t_node **stack_a, t_node **stack_b);
int			get_stack_size(t_node *stack);
void		sort_stack(t_node **stack_a, t_node **stack_b);
int			is_sorted(t_node *stack);

void		swap(t_node **stack);
void		sa(t_node **stack_a);
void		sb(t_node **stack_b);
void		ss(t_node **stack_a, t_node **stack_b);

void		reverse_rotate(t_node **stack);
void		rra(t_node **stack_a);
void		rrb(t_node **stack_b);
void		rrr(t_node **stack_a, t_node **stack_b);

void		add_front(t_node **head, t_node *new);
void		push(t_node **dst, t_node **src);
void		pb(t_node **stack_a, t_node **stack_b);
void		pa(t_node **stack_a, t_node **stack_b);

void		rotate(t_node **stack);
void		ra(t_node **stack_a);
void		rb(t_node **stack_b);
void		rr(t_node **stack_a, t_node **stack_b);

int			find_min_index(t_node *stack);
int			sorting_5(t_node **stack_a, t_node **stack_b);
int			sorting_4(t_node **stack_a, t_node **stack_b);
int			sorting_3(t_node **stack_a);

int			ft_range(t_node **stack_a);
int			protect(t_node **stack_a);
void		init_push_b(t_node **stack_a, int *index, int *range,
				int *test);
void		push_to_b(t_node **stack_a, t_node **stack_b);

void		index_stack(t_node *stack);
void		add_index(t_node *stack);

void		stack_clear(t_node **head);
int			push_back(t_node **head, int n);
t_node		*new_stack(int n);

void		free_arr(char **tmp);
int			is_valid_number(char *tmp);
int			has_duplicates(long n, t_node *a);
int			err_exit(t_node **head, char **arr);
int			parse_input(int ac, char **av, t_node **a);

int			ft_isdigit(int c);
char		**ft_split(char const *s, char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *str);

#endif
