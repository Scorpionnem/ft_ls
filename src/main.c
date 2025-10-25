/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:44:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/25 14:32:22 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

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
			if (!new->is_hidden && ctx->flags.R_flag && new->is_dir)
				get_files(ctx, new, &new->dir);
			files_add_back(parent_dir, new);
		}
	}
	while (dirent);
	closedir(dir);
	return (1);
}

void	print_file(t_ctx *ctx, t_file *file)
{
	(void)ctx;
	if (file->is_hidden && !ctx->flags.a_flag)
		return ;
	if (!ctx->flags.l_flag)
		printf("%s ", file->name);
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

		printf("%lu %s %s %ld	%s %s\n", file_stat.st_nlink, passwd->pw_name, group->gr_name, file_stat.st_size, time_string, file->name);
	}
}

void	print_files(t_ctx *ctx, t_file *file)
{
	t_file	*tmp = file->dir;

	if (!file->is_dir)
		return print_file(ctx, file);

	if (ctx->flags.R_flag)
		printf("%s:\n", file->path);
	file = file->dir;
	while (file)
	{
		print_file(ctx, file);
		file = file->next;
	}
	if (!ctx->flags.l_flag)
		printf("\n");

	if (ctx->flags.R_flag)
	{
		while (tmp)
		{
			if (tmp->is_dir && !tmp->is_hidden)
			{
				printf("\n");
				print_files(ctx, tmp);
			}
			tmp = tmp->next;
		}
	}
}

int	list_files(t_ctx *ctx, char *path)
{
	t_file	*file = files_new(path, NULL);
	if (!file)
		return (0);
	if (!get_files(ctx, file, &file->dir))
		return (0);

	print_files(ctx, file);
	files_free(file);
	return (1);
}

int	main(int ac, char **av)
{
	t_ctx	ctx;
	t_list	*arg;

	ac = 42;
	if (!ctx_init(&ctx, ++av))
		return (EXIT_FAILURE);
	arg = ctx.args;
	while (arg)
	{
		if (!list_files(&ctx, arg->content))
			break ;
		arg = arg->next;
	}
	return (ctx_delete(&ctx));
}
