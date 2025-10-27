/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:49:20 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/27 10:01:13 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;

	i = 0;
	while ((ft_tolower(s1[i]) == ft_tolower(s2[i])) && (s1[i] || s2[i]))
		i++;
	return ((unsigned char)ft_tolower(s1[i]) - (unsigned char)ft_tolower(s2[i]));
}
