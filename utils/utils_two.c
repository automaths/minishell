/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:47:38 by nsartral          #+#    #+#             */
/*   Updated: 2022/07/29 15:47:47 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			t;
	long long	x;

	t = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+' || str[i] == ' ')
		if (str[i++] == '-')
			t = -1;
	x = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (x * t > 2147483647)
			return (-1);
		if (x * t < -2147483648)
			return (0);
		x = (x * 10) + (str[i++] - '0');
	}
	x *= t;
	return (x);
}

char	*ft_strdup(const char *str)
{
	char	*ptr;
	size_t	i;
	size_t	n;

	n = ft_strlen(str);
	ptr = (char *) malloc(sizeof(char) * (n + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[n] = '\0';
	i = 0;
	while (i < n)
	{
			ptr[i] = str[i];
			i++;
	}
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*one;
	unsigned char	*two;

	one = (unsigned char *)s1;
	two = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (one[i] && two[i] && one[i] == two[i] && i < n - 1)
		i++;
	return (one[i] - two[i]);
}

