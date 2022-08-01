/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 00:13:19 by jucheval          #+#    #+#             */
/*   Updated: 2022/08/01 18:37:52 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../groshell.h"

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

char	*ft_itoa(int nb, t_garbage **garbage)
{
	char		*dest;
	long long	n;
	int			size;

	n = nb;
	size = ft_len(n);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (exiting_malloc(garbage), NULL);
	add_garbage(garbage, new_garbage(dest, S_CHAR));
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
