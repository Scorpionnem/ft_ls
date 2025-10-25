/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 11:53:28 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/25 12:03:05 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ctx.h"

// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	t_list	*tmp;

// 	if (!lst || !del)
// 		return ;
// 	tmp = *lst;
// 	while (*lst)
// 	{
// 		tmp = (*lst)->next;
// 		ft_lstdelone(*lst, del);
// 		*lst = tmp;
// 	}
// 	*lst = NULL;
// }


void	files_free(t_file *lst)
{
	t_file	*tmp;
	
	if (!lst)
		return ;
	tmp = lst;
	while (lst)
	{
		tmp = (lst)->next;
		if (lst->is_dir)
			files_free(lst->dir);
		free(lst->name);
		free(lst->path);
		free(lst);
		lst = tmp;
	}
}
