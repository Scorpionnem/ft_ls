/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:42:37 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/28 13:31:13 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

void	swap_files(t_file *file1, t_file *file2)
{
	char	*tmp_name = file1->name;
	char	*tmp_path = file1->path;
	bool	tmp_is_hidden = file1->is_hidden;
	bool	tmp_is_dir = file1->is_dir;
	t_file	*tmp_dir = file1->dir;

	file1->name = file2->name;
	file1->path = file2->path;
	file1->is_hidden = file2->is_hidden;
	file1->is_dir = file2->is_dir;
	file1->dir = file2->dir;

	file2->name = tmp_name;
	file2->path = tmp_path;
	file2->is_hidden = tmp_is_hidden;
	file2->is_dir = tmp_is_dir;
	file2->dir = tmp_dir;
}

int	sort_files_name(t_file **files, bool reverse)
{
	t_file	*first = (*files)->dir;
	t_file	*tmp = first;

	if (!tmp)
		return (1);
	while (tmp)
	{
		if (tmp->is_dir)
			sort_files_name(&tmp, reverse);
		if (tmp->next)
		{
			if ((!reverse && ft_strcmp(tmp->name, tmp->next->name) > 0) || (reverse && ft_strcmp(tmp->name, tmp->next->name) < 0))
			{
				swap_files(tmp, tmp->next);
				tmp = first;
				continue ;
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	sort_files_time(t_file **files, bool reverse)
{
	t_file	*first = (*files)->dir;
	t_file	*tmp = first;

	if (!tmp)
		return (1);
	while (tmp)
	{
		if (tmp->is_dir)
			sort_files_time(&tmp, reverse);
		if (tmp->next)
		{
			struct stat	file_stat1;
			struct stat	file_stat2;

			if (stat(tmp->path, &file_stat1) == -1)
				return (perror("ft_ls"), 1);
			if (stat(tmp->next->path, &file_stat2) == -1)
				return (perror("ft_ls"), 1);

			struct timespec t1 = file_stat1.st_mtim;
			struct timespec t2 = file_stat2.st_mtim;

			if ((!reverse && (t1.tv_sec < t2.tv_sec || (t1.tv_sec == t2.tv_sec && t1.tv_nsec < t2.tv_nsec) || (t1.tv_sec == t2.tv_sec && t1.tv_nsec == t2.tv_nsec && ft_strcmp(tmp->name, tmp->next->name) > 0))) || (reverse && (t1.tv_sec > t2.tv_sec || (t1.tv_sec == t2.tv_sec && t1.tv_nsec > t2.tv_nsec) || (t1.tv_sec == t2.tv_sec && t1.tv_nsec == t2.tv_nsec && ft_strcmp(tmp->name, tmp->next->name) > 0))))
			{
				swap_files(tmp, tmp->next);
				tmp = first;
				continue ;
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
