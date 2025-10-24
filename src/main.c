/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:44:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/24 14:15:35 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

void	list_recursively(char *name)
{
	printf("\n%s:\n", name);
	DIR	*dir = opendir(name);
	if (!dir)
		return ;
	struct dirent	*dirent = NULL;
	do
	{
		dirent = readdir(dir);
		if (dirent && dirent->d_name[0] != '.')
			printf("	%s\n", dirent->d_name);
	}
	while (dirent);
	
	dir = opendir(name);
	if (!dir)
		return ;
	dirent = NULL;
	do
	{
		dirent = readdir(dir);
		if (dirent && dirent->d_name[0] != '.')
			if (dirent->d_type == 4)
				list_recursively(ft_strjoin(ft_strjoin(name, "/"), dirent->d_name));
	}
	while (dirent);
}

void	print_dirent(t_ctx *ctx, struct dirent *dirent, char *path)
{
	if (!dirent)
		return ;

	if (dirent->d_name[0] == '.' && !ctx->flags.a_flag)
		return ;

	struct stat	file_stat;

	if (stat(path, &file_stat) == -1)
		return perror("1");

	char	*time_string = ctime(&file_stat.st_ctime);
	time_string[16] = 0;

	struct passwd *passwd = getpwuid(file_stat.st_uid);
	if (!passwd)
		return perror("2");
	struct group *group = getgrgid(file_stat.st_gid);
	if (!group)
		return perror("3");

	if (ctx->flags.l_flag)
		printf("%lu %s %s %ld	%s %s\n", file_stat.st_nlink, passwd->pw_name, group->gr_name, file_stat.st_size, time_string, dirent->d_name);
	else
		printf("%s\n", dirent->d_name);
}

int	list_files(t_ctx *ctx, char *origin_path)
{
	DIR	*dir;
	struct dirent	*dirent;
	
	dir = opendir(origin_path);
	if (!dir)
	{
		perror("ls: cannot access ''");
		return (0);
	}

	dirent = NULL;
	do
	{
		dirent = readdir(dir);
		if (dirent)
		{
			print_dirent(ctx, dirent, ft_strjoin(ft_strjoin(origin_path, "/"), dirent->d_name));
		}
	}
	while (dirent);
	closedir(dir);
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
