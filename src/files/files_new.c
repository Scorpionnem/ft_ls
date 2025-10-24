/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:03:14 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/24 15:44:11 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

t_file	*files_new(char *name, char *path, bool isdir)
{
	t_file	*new_node;

	new_node = malloc(sizeof(t_file));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->path = path;
	new_node->is_directory = isdir;
	new_node->next = NULL;
	new_node->sub_dir = NULL;
	new_node->dir = NULL;
	return (new_node);
}
