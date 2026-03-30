/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:55:56 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/02 15:55:58 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*ft_strjoin_free(char *s1, char *s2, int to_free)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (to_free % 2 == 1)
		free(s1);
	if ((to_free / 2) % 2 == 1)
		free(s2);
	return (result);
}
