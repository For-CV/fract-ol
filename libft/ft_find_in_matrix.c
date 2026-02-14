/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_in_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:02:02 by rafael-m          #+#    #+#             */
/*   Updated: 2026/02/14 15:00:00 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_in_matrix(char **m, char *to_find, int len)
{
	int	i;
	int	m_len;

	if (!m || !to_find || len < 0)
		return (-1);
	i = 0;
	m_len = ft_doubleptr_len(m);
	while (i < m_len)
	{
		if (ft_strnstr(m[i], to_find, len))
			return (i);
		i++;
	}
	return (0);
}
