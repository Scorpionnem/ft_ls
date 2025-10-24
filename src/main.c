/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:44:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/24 10:36:39 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

void	list_recursively(char *name)
{
	printf("\n%s:\n", name);
	DIR	*dir = opendir(name);
	struct dirent	*dirent = NULL;
	do
	{
		dirent = readdir(dir);
		if (dirent && dirent->d_name[0] != '.')
			printf("	%s\n", dirent->d_name);
	}
	while (dirent);
	
	dir = opendir(name);
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

	ac = 42;
	if (!ctx_init(&ctx, ++av))
		return (EXIT_FAILURE);

	return (ctx_delete(&ctx));
}
