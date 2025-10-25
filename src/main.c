/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:44:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/25 11:07:42 by mbatty           ###   ########.fr       */
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
		if (dirent && dirent->d_name[0] != '.')
		{
			new = files_new(dirent->d_name, parent->path);
			if (ctx->flags.R_flag && new->is_dir)
				get_files(ctx, new, &new->dir);
			files_add_back(parent_dir, new);
		}
	}
	while (dirent);
	closedir(dir);
	return (1);
}

void	print_files(t_ctx *ctx, t_file *file)
{
	t_file	*tmp = file->dir;

	if (!file->is_dir)
		printf("%s\n", file->name);
	else
	{
		printf("%s:\n", file->path);
		file = file->dir;
		while (file)
		{
			printf("  %s\n", file->name);
			file = file->next;
		}

		if (ctx->flags.R_flag)
		{
			while (tmp)
			{
				if (tmp->is_dir)
					print_files(ctx, tmp);
				tmp = tmp->next;
			}
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
