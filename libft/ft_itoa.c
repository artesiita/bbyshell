/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcanals- <bcanals-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:18:02 by bcanals-          #+#    #+#             */
/*   Updated: 2024/07/06 14:23:56 by bizcru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

static int	get_num_digits(int n)
{
	int	i;

	i = 1;
	if (n == INT_MIN)
		n = INT_MAX;
	else if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static int	my_abs(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

static void	fill(char *rtrn, int n, int size)
{
	rtrn[size] = 0;
	size--;
	if (n == 0)
		rtrn[0] = 48;
	while (n > 0)
	{
		rtrn[size] = (n % 10) + 48;
		n /= 10;
		size--;
	}
}

static char	*manage_int_min(void)
{
	int		size;
	char	*rtrn;

	size = get_num_digits(INT_MIN) + 1;
	rtrn = malloc(size + 1);
	if (rtrn == NULL)
		return (NULL);
	fill (rtrn, INT_MAX, size);
	rtrn[0] = 45;
	rtrn[size - 1]++;
	rtrn[size] = 0;
	return (rtrn);
}

char	*ft_itoa(int n)
{
	char	*rtrn;
	int		size;

	if (n == INT_MIN)
	{
		rtrn = manage_int_min();
		return (rtrn);
	}
	size = get_num_digits(n);
	if (n < 0)
		size++;
	rtrn = malloc(size + 1);
	if (rtrn == NULL)
		return (NULL);
	fill(rtrn, my_abs(n), size);
	if (n < 0)
		rtrn[0] = 45;
	return (rtrn);
}
