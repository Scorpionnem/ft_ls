/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:13:21 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/24 15:01:12 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

void	files_add_back(t_file **lst, t_file *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
	{
		files_last(*lst)->next = new;
	}
	else
		*lst = new;
}
