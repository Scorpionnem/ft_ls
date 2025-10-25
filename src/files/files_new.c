/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:03:14 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/25 10:55:26 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

static char	*get_path(char *name, char *parent_path)
{
	char	*str;

	if (!parent_path)
		return (ft_strdup(name));
	str = ft_strjoin(parent_path, "/");
	str = ft_strjoin(str, name);
	return (str);
}

t_file	*files_new(char *name, char *parent_path)
{
	t_file		*new_node;
	struct stat	file_stat;

	new_node = malloc(sizeof(t_file));
	if (!new_node)
		return (NULL);
	ft_bzero(new_node, sizeof(t_file));
	new_node->name = ft_strdup(name);
	new_node->path = get_path(ft_strdup(name), parent_path);

	if (lstat(new_node->path, &file_stat) == -1)
		return (0);

	new_node->is_dir = S_ISDIR(file_stat.st_mode);

	return (new_node);
}
