/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:53:18 by amabbadi          #+#    #+#             */
/*   Updated: 2025/02/06 22:53:25 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../ft_printf/ft_printf.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
char	*ft_strchr(char *s, int c);

char	*path(char *cmd, char **envp);
int		exec(char *argv, char **envp);

#endif
