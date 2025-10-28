/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:31:38 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/28 14:30:51 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

bool	should_access_dir(const char *name)
{
	if (!ft_strncmp(name, ".", sizeof(".")) || !ft_strncmp(name, "..", sizeof("..")))
		return (false);
	return (true);
}

int	get_files(t_file *parent, t_file **parent_dir)
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
		ft_putstr_fd("ft_ls: cannot open directory '", 2);
		ft_putstr_fd(parent->path, 2);
		ft_putstr_fd("': ", 2);
		perror("");
		return (0);
	}

	do
	{
		dirent = readdir(dir);
		if (dirent)
		{
			new = files_new(dirent->d_name, parent->path);
			files_add_back(parent_dir, new);
		}
	}
	while (dirent);
	closedir(dir);
	return (1);
}
