/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:42:52 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/28 14:40:29 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

static void	print_mode(mode_t mode)
{
	char	*file_types = "-dcbpls?";
	char	*chars = "rwx";
	mode_t	perms[] = {
		S_IRUSR, S_IWUSR, S_IXUSR,
		S_IRGRP, S_IWGRP, S_IXGRP,
		S_IROTH, S_IWOTH, S_IXOTH
	};
	int type_index = 7;

	if (S_ISREG(mode))
		type_index = 0;
	else if (S_ISDIR(mode))
		type_index = 1;
	else if (S_ISCHR(mode))
		type_index = 2;
	else if (S_ISBLK(mode))
		type_index = 3;
	else if (S_ISFIFO(mode))
		type_index = 4;
	else if (S_ISLNK(mode))
		type_index = 5;
	else if (S_ISSOCK(mode))
		type_index = 6;

	ft_putchar_fd(file_types[type_index], 1);

	for (int i = 0; i < 9; i++)
	{
		char c;
		if ((i == 2 && (mode & S_ISUID)))
		{
			if (mode & perms[i])
				c = 's';
			else
				c = 'S';
		}
		else if (i == 5 && (mode & S_ISGID))
		{
			if (mode & perms[i])
				c = 's';
			else
				c = 'S';
		}
		else if (i == 8 && (mode & S_ISVTX))
		{
			if (mode & perms[i])
				c = 't';
			else
				c = 'T';
		}
		else
		{
			if (mode & perms[i])
				c = chars[i % 3];
			else
				c = '-';
		}
		ft_putchar_fd(c, 1);
	}
	ft_putchar_fd(' ', 1);
}

static void	print_file_long(t_file *file)
{
	struct stat	file_stat;

	if (stat(file->path, &file_stat) == -1)
		return perror("ft_ls");

	char	*time_string = ctime(&file_stat.st_ctime) + 4;
	time_string[12] = 0;

	struct passwd *passwd = getpwuid(file_stat.st_uid);
	if (!passwd)
		return perror("ft_ls");
	struct group *group = getgrgid(file_stat.st_gid);
	if (!group)
		return perror("ft_ls");

	print_mode(file_stat.st_mode);
	ft_putnbr_fd(file_stat.st_nlink, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(passwd->pw_name, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(group->gr_name, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(file_stat.st_size, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(time_string, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(file->name, 1);
	ft_putchar_fd('\n', 1);
}

static bool	has_visible_after(t_ctx *ctx, t_file *file)
{
	if (!file)
		return (false);
	file = file->next;
	while (file)
	{
		if (!file->is_hidden || (file->is_hidden && ctx->flags.a_flag))
			return (true);
		file = file->next;
	}
	return (false);
}

static void	print_file(t_ctx *ctx, t_file *file)
{
	bool	space = has_visible_after(ctx, file);

	if (file->is_hidden && !ctx->flags.a_flag)
		return ;
	if (!ctx->flags.l_flag)
	{
		ft_putstr_fd(file->name, 1);
		if (space)
			ft_putchar_fd(' ', 1);
	}
	else
		print_file_long(file);
}

static void	print_total_size(t_ctx *ctx, t_file *file)
{
	struct stat	file_stat;
	int	total = 0;

	file = file->dir;
	while (file)
	{
		if (!ctx->flags.a_flag && file->is_hidden)
		{
			file = file->next;
			continue ;
		}
			
		if (stat(file->path, &file_stat) == -1)
			return perror("ft_ls");

		total += file_stat.st_blocks / 2;
		file = file->next;
	}
	ft_putstr_fd("total ", 1);
	ft_putnbr_fd(total, 1);
	ft_putchar_fd('\n', 1);
}

void	print_files(t_ctx *ctx, t_file *file)
{
	t_file	*dir = file->dir;
	if (!file->is_dir)
	{
		print_file(ctx, file);
		if (!ctx->flags.l_flag)
			ft_putchar_fd('\n', 1);	
		return ;
	}

	if (ctx->flags.R_flag || ctx->mult_args)
	{
		ft_putstr_fd(file->path, 1);
		ft_putendl_fd(":", 1);
	}
	if (ctx->flags.l_flag)
		print_total_size(ctx, file);
	file = file->dir;
	while (file)
	{
		print_file(ctx, file);
		file = file->next;
	}
	if (!ctx->flags.l_flag && has_visible_after(ctx, dir))
		ft_putchar_fd('\n', 1);
}
