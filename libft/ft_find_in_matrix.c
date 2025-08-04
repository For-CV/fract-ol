/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_in_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:02:02 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/04 18:03:09 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_in_matrix(char **m, char *to_find, int len)
{
	if (!m || !to_find || len < 0)
		return (-1);
	while (len - 1 >= 0)
	{
		if (!ft_strstr(m[len - 1], to_find))
			return (len - 1);
		len--;
	}
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	printf("%d\n", ft_find_in_matrix(argv, "hola", argc - 2));

// }
