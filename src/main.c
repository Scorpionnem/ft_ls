/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:44:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/24 16:14:58 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

int	get_files(t_ctx *ctx, t_directory **cur_dir)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_file			*new;
	t_directory		*new_dir;

	dirent = NULL;
	dir = opendir((*cur_dir)->path);
	if (!dir)
		return (0);
	do
	{
		dirent = readdir(dir);
		if (dirent)
		{
			new = files_new(dirent->d_name, (*cur_dir)->path, dirent->d_type == 4);
			if (!new)
				return (0);
			files_add_back(&(*cur_dir)->files, new);
			if (ctx->flags.R_flag && new->is_directory && new->name[0] != '.')
			{
				new_dir = malloc(sizeof(t_directory));
				new_dir->files = NULL;
				new_dir->path = ft_strjoin(ft_strjoin((*cur_dir)->path, "/"), new->name);
				new->dir = new_dir;
				get_files(ctx, &new_dir);
			}
		}
	}
	while (dirent);
	return (1);
}

void	print_dirs(t_ctx *ctx, t_directory *dir)
{
	t_file	*tmp;

	tmp = dir->files;
	while (tmp)
	{
		if (tmp->is_directory && tmp->dir)
		{
			printf("\n");
			print_files(ctx, tmp->dir);
		}
		tmp = tmp->next;
	}
}

void	print_files(t_ctx *ctx, t_directory *dir)
{
	t_file	*tmp;

	tmp = dir->files;
	printf("%s:\n", dir->path);
	while (tmp)
	{
		if (!ctx->flags.a_flag && tmp->name[0] == '.')
		{
			tmp = tmp->next;
			continue ;
		}
		printf("%s ", tmp->name);
		tmp = tmp->next;
	}
	printf("\n");
	print_dirs(ctx, dir);
}

int	list_files(t_ctx *ctx, char *path)
{
	t_directory	*dir;

	dir = malloc(sizeof(t_directory));
	dir->files = NULL;
	dir->path = path;

	if (!get_files(ctx, &dir))
		return (0);
	print_files(ctx, dir);
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
