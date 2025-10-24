/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:00:21 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/24 10:38:46 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

int		ctx_init(t_ctx *ctx, char **av)
{
	ft_bzero(ctx, sizeof(t_ctx));
	if (!ctx_parse_args(ctx, av))
		return (0);
	return (1);
}

int		ctx_delete(t_ctx *ctx)
{
	(void)ctx;
	return (EXIT_SUCCESS);
}
