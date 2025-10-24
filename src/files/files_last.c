/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:59:38 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/24 15:03:23 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

t_file	*files_last(t_file *lst)
{
	int	count;

	count = files_size(lst);
	while (count > 1)
	{
		lst = lst->next;
		count--;
	}
	return (lst);
}
