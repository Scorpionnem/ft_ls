/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:42:52 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/28 08:51:05 by mbatty           ###   ########.fr       */
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
		ft_putstr_fd(file->name, 1);
		if (space)
			ft_putchar_fd(' ', 1);
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
	if (!file->is_dir)
		return print_file(ctx, file, file->next);

	if (ctx->flags.R_flag)
	{
		ft_putstr_fd(file->path, 1);
		ft_putendl_fd(":", 1);
	}
	file = file->dir;
	while (file)
	{
		print_file(ctx, file, file->next);
		file = file->next;
	}
	if (!ctx->flags.l_flag)
		ft_putchar_fd('\n', 1);
}
