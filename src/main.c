/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:44:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/24 11:02:11 by mbatty           ###   ########.fr       */
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
		list_recursively(arg->content);
		arg = arg->next;
	}	
	return (ctx_delete(&ctx));
}
