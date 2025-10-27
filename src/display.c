/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:42:52 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/27 09:43:14 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

static void	print_file(t_ctx *ctx, t_file *file, bool space)
{
	(void)ctx;
	if (file->is_hidden && !ctx->flags.a_flag)
		return ;
	if (!ctx->flags.l_flag)
	{
		printf("%s", file->name);
		if (space)
			printf(" ");
	}
	else
	{
		struct stat	file_stat;

		if (stat(file->path, &file_stat) == -1)
			return perror("ft_ls");

		char	*time_string = ctime(&file_stat.st_ctime);
		time_string[16] = 0;

		struct passwd *passwd = getpwuid(file_stat.st_uid);
		if (!passwd)
			return perror("ft_ls");
		struct group *group = getgrgid(file_stat.st_gid);
		if (!group)
			return perror("ft_ls");

		printf("%lu %lu %s %s %ld	%s %s\n", file_stat.st_blocks, file_stat.st_nlink, passwd->pw_name, group->gr_name, file_stat.st_size, time_string, file->name);
	}
}

void	print_files(t_ctx *ctx, t_file *file)
{
	t_file	*tmp = file->dir;

	if (!file->is_dir)
		return print_file(ctx, file, file->next);

	if (ctx->flags.R_flag)
		printf("%s:\n", file->path);
	file = file->dir;
	while (file)
	{
		print_file(ctx, file, file->next);
		file = file->next;
	}
	if (!ctx->flags.l_flag)
		printf("\n");

	if (ctx->flags.R_flag)
	{
		while (tmp)
		{
			if (tmp->is_dir && (!tmp->is_hidden || (ctx->flags.a_flag && should_access_dir(tmp->name))))
			{
				printf("\n");
				print_files(ctx, tmp);
			}
			tmp = tmp->next;
		}
	}
}
