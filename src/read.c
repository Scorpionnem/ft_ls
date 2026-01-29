/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:31:38 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/29 14:09:36 by mbatty           ###   ########.fr       */
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

	struct stat	file_stat;

	lstat(parent->path, &file_stat);
	if (!S_ISDIR(file_stat.st_mode))
		return (1);

	dirent = NULL;
	dir = opendir(parent->path);
	if (!dir)
	{
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
			if (!new)
				return (0);
			files_add_back(parent_dir, new);
		}
	}
	while (dirent);
	closedir(dir);
	return (1);
}
