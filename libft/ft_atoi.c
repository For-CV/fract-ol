/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:28:02 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/16 17:54:30 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

The  atoi()  function  converts the initial portion of the string pointed to by
nptr to int.  The behavior is the same as

           strtol(nptr, NULL, 10);

except that atoi() does not detect errors.

RETURN VALUE
       The converted value or 0 on error.
*/

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	result = 0;
	i = 0;
	sign = 1;
	if (!str)
		return (0);
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = 1 - 2 * (str[i] == '-');
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
/*
int     main(void)
{
        char    *nbr = "  \t  -0\t12";
        int     result;

        result = ft_atoi(nbr);
        printf("ft_atoi = %d\n", result);
        result = atoi(nbr);
        printf("atoi = %d\n", result);
}*/
