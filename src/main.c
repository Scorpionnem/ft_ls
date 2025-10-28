/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:44:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/28 14:31:50 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

int	list_files_pipeline(t_ctx *ctx, t_file *file)
{
	t_file	*tmp;

	if (!get_files(file, &file->dir))
		return (1);
	if (!ctx->flags.t_flag)
		sort_files_name(&file, ctx->flags.r_flag);
	else
		sort_files_time(&file, ctx->flags.r_flag);
	print_files(ctx, file);
	tmp = file->dir;
	while (tmp)
	{
		if (ctx->flags.R_flag && tmp->is_dir && should_access_dir(tmp->name)
			&& ((ctx->flags.a_flag && tmp->is_hidden) || !tmp->is_hidden))
		{
			ft_putchar_fd('\n', 1);
			list_files_pipeline(ctx, tmp);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	list_files(t_ctx *ctx, char *path)
{
	t_file	*file = files_new(path, NULL);
	if (!file)
		return (0);
	if (!list_files_pipeline(ctx, file))
		return (0);
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
		if (arg->next)
			ft_putchar_fd('\n', 1);
		arg = arg->next;
	}
	return (ctx_delete(&ctx));
}
