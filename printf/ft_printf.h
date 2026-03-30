/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:10:54 by amabbadi          #+#    #+#             */
/*   Updated: 2025/01/19 22:38:42 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *input, ...);
int	ft_putstr(char *str);
int	ft_putnbr(int n);
int	ft_putchar(char c);
int	ft_putuint(unsigned int num);
int	ft_putptr(void *ptr);
int	ft_putx(unsigned int num);
int	ft_putxa(unsigned int num);

#endif
