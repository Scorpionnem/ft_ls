/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:00:21 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/28 14:25:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

void	empty_del(void *ptr)
{
	(void)ptr;
}

int		ctx_init(t_ctx *ctx, char **av)
{
	ft_bzero(ctx, sizeof(t_ctx));
	if (!ctx_parse_args(ctx, av))
		return (0);
	ctx->mult_args = ft_lstsize(ctx->args) > 1;
	sort_args_name(&ctx->args);
	return (1);
}

int		ctx_delete(t_ctx *ctx)
{
	ft_lstclear(&ctx->args, empty_del);
	return (EXIT_SUCCESS);
}
