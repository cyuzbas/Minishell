/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:47:47 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/06 17:47:48 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_chars(int val)
{
	int	num_d;

	if (val == 0)
		return (1);
	num_d = 0;
	if (val < 0)
	{
		val *= -1;
		num_d++;
	}
	while (val > 0)
	{
		val /= 10;
		num_d++;
	}
	return (num_d);
}

void	ft_putnbr_fd(int n, int fd)
{
	size_t	index;
	char	str[12];

	if (n == 0)
		return (ft_putchar_fd('0', fd));
	else if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	index = num_chars(n);
	str[index] = '\0';
	index--;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[index] = (n % 10) + '0';
		n /= 10;
		index--;
	}
	ft_putstr_fd(str, fd);
}
