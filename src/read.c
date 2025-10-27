/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:31:38 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/27 09:40:36 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

bool	should_access_dir(const char *name)
{
	if (!ft_strncmp(name, ".", sizeof(".")) || !ft_strncmp(name, "..", sizeof("..")))
		return (false);
	return (true);
}

int	get_files(t_ctx *ctx, t_file *parent, t_file **parent_dir)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_file			*new;

	dirent = NULL;
	dir = opendir(parent->path);
	if (!dir)
	{
		if (errno == ENOTDIR)
			return (1);
		perror("");
		return (0);
	}

	do
	{
		dirent = readdir(dir);
		if (dirent)
		{
			new = files_new(dirent->d_name, parent->path);
			if (ctx->flags.R_flag && new->is_dir && should_access_dir(new->name))
				get_files(ctx, new, &new->dir);
			files_add_back(parent_dir, new);
		}
	}
	while (dirent);
	closedir(dir);
	return (1);
}
