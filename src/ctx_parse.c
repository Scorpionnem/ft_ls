/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:33:20 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/24 10:55:54 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

static void	ctx_set_flag(t_ctx *ctx, char flag)
{
	ctx->flags.l_flag = flag == 'l';
	ctx->flags.R_flag = flag == 'R';
	ctx->flags.a_flag = flag == 'a';
	ctx->flags.r_flag = flag == 'r';
	ctx->flags.t_flag = flag == 't';
}

static int	ctx_parse_flag(t_ctx *ctx, char *flags)
{
	int	i;

	i = -1;
	while (flags[++i])
	{
		if (!ft_strchr(VALID_FLAGS, flags[i]))
		{
			ft_putstr_fd("ft_ls: invalid option '", 2);
			ft_putchar_fd(flags[i], 2);
			ft_putendl_fd("'", 2);
			return (0);
		}
		ctx_set_flag(ctx, flags[i]);
	}
	return (1);
}

static int	ctx_add_argument(t_ctx *ctx, char *av)
{
	t_list	*new = ft_lstnew(av);
	if (!new)
	{
		ft_lstclear(&ctx->args, empty_del);
		return (0);
	}
	ft_lstadd_back(&ctx->args, new);
	return (1);
}

int	ctx_parse_args(t_ctx *ctx, char **av)
{
	int	i;

	i = -1;
	while (av[++i])
	{
		if (av[i][0] == '-')
		{
			if (!ctx_parse_flag(ctx, ++av[i]))
				return (0);
		}
		else
			ctx_add_argument(ctx, av[i]);
	}
	return (1);	
}
