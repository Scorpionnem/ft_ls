/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:03:14 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/28 16:21:09 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

static char	*get_path(char *name, char *parent_path)
{
	char	*str;
	char	*str2;

	if (!parent_path)
		return (ft_strdup(name));
	str = ft_strjoin(parent_path, "/");
	str2 = ft_strjoin(str, name);
	free(str);
	return (str2);
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
	new_node->path = get_path(name, parent_path);

	if (lstat(new_node->path, &file_stat) == -1)
	{
		free(new_node->name);
		free(new_node->path);
		free(new_node);
		perror("ft_ls");
		return (0);
	}

	new_node->is_hidden = new_node->name[0] == '.';

	new_node->is_dir = S_ISDIR(file_stat.st_mode);

	return (new_node);
}
