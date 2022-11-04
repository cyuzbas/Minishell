/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:46:29 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/06 17:46:31 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	mk_abs(int n)
{
	if (n < 0)
		n *= -1;
	return ((unsigned int) n);
}

static unsigned int	max_pow(unsigned int val)
{
	unsigned long	pow_ten;

	if (val < 10)
		return (1);
	pow_ten = 1;
	while (pow_ten <= val)
		pow_ten *= 10;
	pow_ten /= 10;
	return ((unsigned int) pow_ten);
}

static int	num_digits(unsigned int val)
{
	int	num_d;

	num_d = 0;
	if (!val)
		return (1);
	while (val > 0)
	{
		val /= 10;
		num_d++;
	}
	return (num_d);
}

static void	mk_str(unsigned int num, unsigned int pow, char *str, int sign)
{
	unsigned int	div;
	int				iter;

	iter = 0;
	if (sign == -1)
	{
		str[iter] = '-';
		iter++;
	}
	while (pow >= 1)
	{
		div = num / pow;
		num = num % pow;
		pow /= 10;
		str[iter] = div + '0';
		iter++;
	}
	str[iter] = '\0';
}

char	*ft_itoa(int n)
{
	unsigned int	val;
	unsigned int	pow;
	char			*str;
	int				sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	val = mk_abs(n);
	pow = max_pow(val);
	if (sign == 1)
	{
		str = (char *) malloc(num_digits(val) * sizeof(char) + 1);
		if (!str)
			return (str);
	}
	else
	{
		str = (char *) malloc(num_digits(val) * sizeof(char) + 2);
		if (!str)
			return (str);
	}
	mk_str(val, pow, str, sign);
	return (str);
}
