/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 04:10:50 by amabbadi          #+#    #+#             */
/*   Updated: 2024/11/16 17:40:20 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	t_list	*create_and_append(t_list **newlist,
		void *content, void (*del)(void *))
{
	t_list	*newnode;

	newnode = ft_lstnew(content);
	if (!newnode)
	{
		ft_lstclear(newlist, del);
		del(content);
		return (NULL);
	}
	ft_lstadd_back(newlist, newnode);
	return (newnode);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	void	*newcontent;

	newlist = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		newcontent = f(lst->content);
		if (newcontent && !create_and_append(&newlist, newcontent, del))
			return (NULL);
		lst = lst->next;
	}
	return (newlist);
}
