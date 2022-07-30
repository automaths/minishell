/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 00:13:19 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/31 00:13:29 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	ft_len(long long nb)
{
	long long	n;
	int			count;

	n = nb;
	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int nb)
{
	char		*dest;
	long long	n;
	int			size;

	n = nb;
	size = ft_len(n);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size--] = '\0';
	if (n == 0)
		dest[size] = '0';
	if (n < 0)
	{
		dest[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		dest[size] = ((n % 10) + '0');
		n /= 10;
		size--;
	}
	return (dest);
}